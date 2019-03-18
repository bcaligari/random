# Miscellaneous test cases

## Utilities

* `./misc/zombiemaker` - create a number of zombies
* `./misc/orphaniser` - orphan some child processes and log their reparenting
* `./misc/forkbomber` - create a number of children or fork until error
* `./misc/segfaulter` - segfaults
* `./misc/memeater` - eats memory (allocates and zero fills blocks until killed or sytem barfs)

## Notes

### Generating core dumpfiles
* `$ ulimit -c unlimited`
* `# sysctl kernel.core_pattern=core.%p`
