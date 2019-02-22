# Miscellaneous test cases

## Utilities

* `zombiemaker` - create a number of zombies
* `orphaniser` - orphan some child processes and log their reparenting
* `forkbomber` - create a number of children or fork until error
* `segfaulter` - segfaults

## Notes

### Generating core dumpfiles
* `$ ulimit -c unlimited`
* `# sysctl kernel.core_pattern=core.%p`
