# Miscellaneous test cases

## Utilities

* `./misc/zombiemaker` - create a number of zombies
* `./misc/orphaniser` - orphan some child processes and log their reparenting
* `./misc/forkbomber` - create a number of children or fork until error
* `./misc/segfaulter` - segfaults
* `./misc/clone-pid-tid` - clone(2) a thread and wait for it to finish
* `./misc/getuid` - prints uid, euid, gid, egid

### `./memeater/*`

* eats memory - binary, static, container, k8s pod
* Test Kubernetes Pod memorylimits

### `./misc/writer-write2.c`

* `write(2)` to a file in a loop
* Test mount behaviour of NFS volumes

### `./maxmmap/maxmmap.c`

* `mmap(2)` until process falls over
* Needed by colleague

## Misc

### Generating core dumpfiles
* `$ ulimit -c unlimited`
* `# sysctl kernel.core_pattern=core.%p`
