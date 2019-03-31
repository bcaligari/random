# Miscellaneous test cases

## Utilities

* `./misc/zombiemaker` - create a number of zombies
* `./misc/orphaniser` - orphan some child processes and log their reparenting
* `./misc/forkbomber` - create a number of children or fork until error
* `./misc/segfaulter` - segfaults
* `./memeater/*` - eats memory - binary, static, container, k8s pod

## Notes

### Generating core dumpfiles
* `$ ulimit -c unlimited`
* `# sysctl kernel.core_pattern=core.%p`
