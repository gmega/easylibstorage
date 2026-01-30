I want you to implement the API described in easylibstorage.h in a file name easylibstorage.c. This is a simplified
wrapper on top of libstorage. You can find the headers for libstorage here:

- /home/giuliano/Work/Status/logos-storage-nim/library/libstorage.h

You can find examples of how to use libstorage here:

- /home/giuliano/Work/Status/logos-storage-nim/examples/c/examples.c

I want you to implement one function at a time. You MUST follow a Test Driven Development approach where you:

1. write a test for a function; (red)
2. write the function;
3. run it until your test is green; (green)
4. stop, think of ways to refactor and simplify the code, and do it; (refactor)
5. once you're done refactoring and the tests are green, move to the next function. This step is VERY IMPORTANT. You MUST look for ways to simplify,
deduplicate, and coalesce code here, WITHOUT OVERCOMPLICATING. SIMPLICITY
IS KEY AND YOUR GUIDING PRINCIPLE.

Feel free to use an idiomatic C way to write your unit tests, but DO NOT implement the next function before doing
the full 1-5 cycle first. You need to follow the red-greed-refactor tenets of TDD.

Finally, I want you to wire all of the above in the console application under main.c. This console application must
support the following commands:

- help (prints help)
- start [API PORT] [DISCOVERY PORT] [BOOTSTRAP NODE] - creates and starts the node, all parameters are mandatory.
- stop - stops and destroys the node
- upload [LOCAL PATH] - uploads a local file to the node. Shows simple progress, prints the CID on screen when done.
- download [CID] [LOCAL PATH] - downloads a remote CID to a local path. Shows simple progress, prints CID on screen when done.

If needed, the code for libstorage can also be found under /home/giuliano/Work/Status/logos-storage-nim/library.
