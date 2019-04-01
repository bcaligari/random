## Mem Eater

Silly little program to allocate memory until something happens.

### Usage

`memeater [-i secs] [-s bytes] [-c count] [-f logfile]`

```{text}
$ ulimit -v $((16*1024))
$ ./memeater -i 1 -s $((2*1024*1024))
1365: Consuming 2097152 bytes (2 MiB); 1 second intervals; -1 max iterations
1365: Allocating aggregate of 2097152 bytes (2 MiB)
1365: Allocating aggregate of 4194304 bytes (4 MiB)
...
1365: Allocating aggregate of 12582912 bytes (12 MiB)
1365: malloc(3) failed: Cannot allocate memory (12)
```

#### Binaries

* `memeater` - ordinary binary
* `memeater-static` - statically built version of `memeater`.
* `bcaligari/memeater` - docker container image of `memeater-static`.

#### Parameters

* `-i secs` - seconds to wait after each `malloc(3)` / `memset(3)`.
* `-s bytes` - size of `malloc`.
* `-c count` - number of iterations before `pause(2)`. -1 (default) for infinite.
* `-f logfile` - log file to write to.

### Running as a K8s Pod

* Use [or start with] the included manifest.
    * `$ kubectl create -f k8s-manifest.yaml`
* Two Containers one Pod.
    * `memeater` - the Pod.
        * `memeater` - as the name implies - based on *busybox*.
        * `sideshell` - a companion shell for fun and games - based on *alpine*.
* `sideshell` installs `strace` via `postStart`. Bit naughty.
* Illustrating behaviour.
    * `$ kubectl attach -it memeater -c sideshell`
        * `# ps aux`
        * `# tail -f /opt/memeater/log/memeater.log`
        * `# strace -p <pid>`

### Build Options

* `make memeater` - build an ordinary binary.
* `make memeater-static` - build memeater as a static binary.
* `make container` - build a docker image from memeater-static.
* `docker push bcaligari/memeater` - push container to Docker Hub.

### TODO

* Code cleanup.
* Generalise container & k8s manifest building.
* Makefile properly.
