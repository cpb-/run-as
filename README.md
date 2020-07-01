# run-as

Simple tool to run a command as a non-priviledged user in boot scripts.

The aim of this project is to start custom code from boot script (especially in small embedded Linux systems) with credentials different than root.

## Usage

```
run-as  <user-ID>  <group-ID>  <command-line>
```

For example:

```
run-as  1000  1000  /home/user/custom-application &
```

## Author

Christophe BLAESS 2019-2020. <christophe.blaess@logilin.fr>

## License

This software is distributed under the terms of the Gnu GPL v.2 license.
