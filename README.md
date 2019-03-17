# Miscellaneous test cases

## Utilities

* `zombiemaker` - create a number of zombies
* `orphaniser` - orphan some child processes and log their reparenting
* `forkbomber` - create a number of children or fork until error
* `segfaulter` - segfaults
* `memeater` - eats memory (allocates and zero fills blocks until killed or sytem barfs)

## Notes

### Generating core dumpfiles
* `$ ulimit -c unlimited`
* `# sysctl kernel.core_pattern=core.%p`
