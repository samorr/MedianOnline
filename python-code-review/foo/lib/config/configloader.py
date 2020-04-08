import os
from typing import Optional

import boto3
import yaml


class ConfigLoaderException(Exception):
    pass


class Config:

    def __init__(self, config: dict, source: str):
        self._config = config
        self._source = source

    @property
    def source(self):
        return self._source

    def __repr__(self):
        return (f'Config(config={self._config!r}'
                f'       source={self.source!r})')

    def __getattr__(self, name):
        return self._config[name]

    def __getitem__(self, name):
        return self._config[name]

    def get(self, name, default=None):
        return self._config.get(name, default)


class ConfigLoader:

    """Loads configuration files.

    Source of the config depends on the currently set environment (either
    'test' or 'prod', as dictated by the *env* file.
    """

    S3_BUCKET = 'configs'
    _instance = None
    _instance_ready = False

    # Make this class a singleton since usually config is loaded only once.
    def __new__(cls, *args, **kwargs):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
        return cls._instance

    def __init__(self, defaults: dict = {}):
        if self._instance_ready:
            return
        self.defaults = defaults
        env: str = open('env').read().strip()
        print(f'Current environment is: {env!r}')
        if env == 'test':
            self._handler = self._local_loader
        elif env == 'prod':
            self._handler = self._s3_loader
        self._config: Optional[Config] = None
        self._instance_ready = True

    def _local_loader(self, path: str) -> dict:
        try:
            with open(path) as f:
                config = yaml.load(f)
        except Exception:
            raise ConfigLoaderException(f'Error opening {path}')
        return config

    def _s3_loader(self, path: str) -> dict:
        try:
            f = boto3.client('s3').download_fileobj(self.S3_BUCKET, path)
            config = yaml.load(f)
        except Exception:
            raise ConfigLoaderException(f'Error when opening {path}')
        return config

    def load(self, path: str) -> Config:
        if self._config:
            return self._config
        config = self._handler(path)
        environ = os.environ
        for key in config:
            if key in environ:
                config[key] = os.environ[key]
        for key in self.defaults:
            if key not in config:
                config[key] = self.defaults[key]
        self._config = Config(config, path)
        return self._config

    def reset(self):
        self._config = None
