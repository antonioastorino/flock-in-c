# flock in C 

## Motivation
Try and search for "Flock in C" on YouTube. You won't find this stuff.

## Build and run
```bash
./build-and-run.sh
```

## Explanation
This tiny project is to show how to use a file to share data between 2 processes. For simplicity, a producer and a consumer are created within the same executable.

The producer uses `flock` with the "exclusive" flag. That is because the producer wants nobody else to access the file while it is being written. Also, the producer prefers to wait for readers to complete reading. Hence, the producer blocks until the readings are in progress.

The consumer uses the "shared" flag. In fact, while the shared file is being written, other processes are allowed to read it but the producer(s) should not access it for writing. Also, the consumer doesn't want to get stuck if the file is locked. Therefore, the consumer uses the "non-block" flag.

## Resources
- [TutorialsPoint](https://www.tutorialspoint.com/unix_commands/flock.htm)
