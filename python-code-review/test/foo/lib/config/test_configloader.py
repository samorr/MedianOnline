import pytest

from foo.lib.config import ConfigLoader, ConfigLoaderException


def test_load(monkeypatch):
    loader = ConfigLoader(defaults={'VAR0': 'default value 0',
                                    'VAR1': 'default value 1'})
    monkeypatch.setenv('VAR3', 'not bar')
    config = loader.load('test/foo/lib/config/config.yaml')
    assert config._config == {'VAR0': 'fizz',
                              'VAR1': 'default value 1',
                              'VAR2': 'foo',
                              'VAR3': 'not bar'}
    assert config.source == 'test/foo/lib/config/config.yaml'


def test_load_missing():
    loader = ConfigLoader()
    loader.reset()
    with pytest.raises(ConfigLoaderException):
        loader.load('test/foo/lib/config/missing-config.yaml')


def test_is_a_singleton():
    assert ConfigLoader(defaults={'VAR0': 'default value 0'}) is ConfigLoader()
