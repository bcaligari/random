# Troubleshooting one liners

## Processes in uninterruptible sleep

The load average is the average sum of runnable, running, and uninterruptible
sleep tasks over the past 1, 5, and 15 minutes.  Therefore, every task in
in uninterruptible sleep is adding 1 to the load average.

### Checking the load average

```{text}
uptime
```

```{text}
cat /proc/loadavg
```

### Identifying blocked tasks

```{text}
ps -eo pid,stat,comm | awk '$2 ~ "^D" {print}'
```

```{text}
ps -eo pid,stat,wchan:24,%cpu,%mem,args --forest
```

### Dumping tasks in uninterruptible state

This output should persist in systemd journal.

```{text}
echo w > /proc/sysrq-trigger
````

`t` instead of `w` will dump all tasks instead.

We can view the stack of a single PID.

```{text}
cat /proc/<PID>/stack
```

## Network connectivity

* `nmap` - Network exploration tool
* `nc` - arbitratry TCP and UDP connections and listens
* `tcpdump` - dump traffic on a network

Check whether a remote TCP port is answering

```{text}
nmap -p <PORT> <IP>
```

Check which application, if any, is listening on a particular TCP port

```{text}
ss -tlnp 'sport == 22'
```

Check all connections, listening or established, on a particular TCP port

```{text}
ss -tanp 'sport == 22'
```

An program will not show if the endpoint is managed by the kernel

```{text}
ss -tanp 'sport == 3260'
```

Check for traffic against a local TCP port

```{text}
tcpdump -i eth1 -n tcp port 3260
```

## Open \[but possibly deleted\] files

* `lsof` - list open files
  * Lists files by the *link* used to open the file.  As in UNIX, on Linux
    there may be more than one link \(filename\) pointing to a single inode.
  * Therefore the same file may have been opened using different names.
  * If the opening link has been deleted the filename will be suffixed
    with `(deleted)`.
* `fuser` - identify processes using files or sockets

List all open files

```{text}
lsof
```

List open files for a specific process

```{text}
lsof -p <PID>
```

```{text}
fuser -uv <NAME>
```
