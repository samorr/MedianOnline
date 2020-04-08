# foo-config-loader

A config loader for the Foo project.


# Project tasks

## In order to setup a local env run...:

    virtualenv create -p python3.6 venv/
    ./venv/bin/pip install pip-tools
    ./venv/bin/pip install -r requirements.txt requirements-test.txt

## In order to update the requirements run...:

    ./venv/bin/pip-compile requirements.in
    ./venv/bin/pip-compile requirements-test.in

## In order to execute tests run...:

    env PYTHONPATH=. ./venv/bin/pytest test
