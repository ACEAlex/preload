# Having fun with LD_PRELOAD

All code can be found on github. 

git clone https://github.com/ACEAlex/preload.git

Lets use LD_PRELOAD to inject code to hack
our testprog.

Normal execution steps
======================

A very simplified explanaton of what happens when system
starts/executes our testprog. I.e. the following command
is issued. **./testprog**

1. System loads our binary **testprog**
2. Some of the symbols (fopen, fgets, rand) are dynamically
   loaded as shared libraries. They are in testprog *undefined*
   and the dynamic linker will find and load the shared library.
   It will then bind the corresponding shared-lib function in the code.
3. Execution is started.

testprog
   - UND fopen@GLIBC_2.2.5 (2) 
                   I
                   I
                   I Dynamic linker loads and binds function references
                   I
                   V
          fopen in libc.so.6



Injecting our code via LD_PRELOAD
=================================
LD_PRELOAD instructs loader to **PRELOAD** a shared library
before doing the normal loading rutine. This enable us to inject
our own code in the execution.

LD_PRELOAD=./haxer.so ./testprog

testprog
   - UND fopen@GLIBC_2.2.5 (2) 
                   I
                   I Dynamic linker loads haxer.so
                   I
                   v
           fopen in haxer.so


But wait! Wouldnt it be great if we also could call the original 
fopen code from our code? Like this

testprog
   - UND fopen@GLIBC_2.2.5 (2) 
                   I
                   I Dynamic linker loads haxer.so
                   I
                   v
           fopen in haxer.so
                   I
                   I Our code calls original fopen
                   I
                   V
          fopen in libc.so.6
               
And yes we can. Lets se how.

/Alexander Saers
