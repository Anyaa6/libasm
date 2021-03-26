# libasm
An Intel x64 bits assembly library

1# Do "make"
2# Do "./a.out"
3# you can change the main.c to test my asm functions


reste strcmp et dup a corriger // nettoyer fichier et rendre

**Language d'assembleur** : et non pas language assembleur, l'assembleur n'est pas un language mais l'**outil** qui va assembler les traductions (par compilation) en language *machine* pour en faire un programme

Chaque processeur a son propre language avec un **jeu d'instructions** fournit par le constructeur du processeur ~le menu de ce que ce language peux faire. Ce sont des opérations tres simples et c'est la combinaison de ces operations qui vont permettre d'avoir des fonctionnalités interessantes

→ Quasiment pas de portabilité du code

Sur Linux on a accres aux appels system → syscalls alors que sur windows il faut rajouter une API pour y avoir acces

## Registers

[https://www.youtube.com/watch?v=fpnE6UAfbtU&ab_channel=CrashCourse](https://www.youtube.com/watch?v=fpnE6UAfbtU&ab_channel=CrashCourse)

- latches = circuit de logic gates qui permet de contenir/enregistrer un **etat (1 ou 0) /** une valeur en renvoyant l'output d'un logic gate vers son entrée (dans un logic gate normal on est toujours en marche en avant)
- **Register** = ensemble de latches qui retient un nombre en binaire, le nombre de 1 et 0 qu'il contient est appelé la **largeur** d'un register, c'est la mémoire la plus rapide d'un ordinateur. Donc si register de 8 alors il permet de stocker un byte / 8 bits. *A register is a temporary storage area built into a CPU.* De nos jours de nombreux ordi ont des registre de taille 64 (taille d'un *bus*).

Une architecture externe de processeur définit un **ensemble de registres**, dits architecturaux, qui sont **accessibles par son jeu d'instructions** en language d'assembleur.

Un processeur peut contenir plusieurs centaines de registres, mais, à titre d’exemple, un processeur Intel 32 bits en contient seize2. Chaque registre a une capacité de 8, 16, 32 ou 64 bits

### Calling convention

→ specifies how a function call in C or C++ is converted into assembly language, c'est l'ordre des parametres (atomiques ou complexes). 

The calling convention of the **System V AMD64 ABI** is followed on Solaris, Linux, FreeBSD, **macOS**

Intel instructions have the **destination register first**, and the source register second.

`rax` - contains **return value of functions** (d'ou le fait qu'en C il ne peux y avoir qu'une valeur de retour) **OR** when we **syscall**, rax must contain syscall number

> 1 `rdi` → 2 `rsi` → 3 `rdx` → 4 `rcx` (ou R10) → 5 `r8` → 6 `r9`

→ For system calls, R10 is used instead of RCX.

→ **Additional parameters** are pushed on the **stack, right to left** (donc le dernier parametre est le plus deep dans la file) and are to be ***removed*** by the caller after the call

→the return value is stored in RAX.

→ The only registers that the called function is required to preserve (the calle-save registers) are: rbp, rbx, r12, r13, r14, r15. All others are free to be changed by the called function.

→ **main** est elle-meme une fonction donc quand elle est appelee : **argc will end up in rdi, and argv (a pointer) will end up in rsi**

Ordre d'utilisation des registres, hors syscall :

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/d1afa002-b258-48ee-969e-20a604befa73/Untitled.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/d1afa002-b258-48ee-969e-20a604befa73/Untitled.png)

### Instruction de Comparaison `cmp` // Instructions conditionnelles

va se baser sur les flags / indicateurs dont la valeur est fixee par l'UAL **apres instruction logique ou arithmetique**. Les indicateurs font partie de ce que l'on appelle le **registre d'état qui n'est pas directement accessible par les autres instructions**, seules des **instructions spécifiques** permettent de les **manipuler.**

**C - Carry Flag** : c'est l'indicateur de retenue.

**O - Overflow Flag** : lorsque le nombre de bits sur lesquels les nombres sont codés n'est pas suffisant et que le résultat d'une opération n'est pas codable avec le nombre de bits spécifiés

**S - Sign Flag** : le signe du bit de poids fort.

**Z - Zero Flag** : permet de savoir si le résultat de la dernière opération était nul, dans ce cas, l'indicateur ZF est positionné à 1

On va notamment les utiliser pour l'instruction `cmov**cc**` ****ou cc represente l'etatd es flags attendus, exemple 

`cmovno x, y` va set x ← y si `n`ot `o`verflow ****

`cmovo x, y` va set x ← y si `o`verflow

`setc x` va set x ← 1 si la derniere operation avait `carry` flag sinon set a 0

The conditional instructions have three base forms: j for conditional jump, cmov for conditional move, and set for conditional set. The suffix of the instruction has one of the **30 forms**: s ns z nz c nc o no p np pe po e ne l nl le nle g ng ge nge a na ae nae b nb be nbe 

liste extensive de branchements conditionnels ici : p32 [http://www2.ift.ulaval.ca/~marchand/ift17583/Supplement2.pdf](http://www2.ift.ulaval.ca/~marchand/ift17583/Supplement2.pdf)

- Instructions conditionnelles

    `jmp` est jump inconditionnel

    - `JE` - if equal
    - `JZ` - if zero
    - `JNE` - if not equal
    - `JNZ` - if not zero
    - `JG` - if first operand is greater than second
    - `JGE` - if first operand is greater or equal to second
    - `JA` - the same that JG, but performs unsigned comparison
    - `JAE` - the same that JGE, but performs unsigned compariso
    - **JA** Jump if above

        effectue un saut si **ZF=0 et CF=0** 

    - **JB** Jump if Below

        effectue un saut si **CF=1** 

    - **JBE** jump if below or equal

        effectue un saut si **ZF=1 ou CF=1**

    - **JE** Jump if Equal

        effectue un saut si **ZF=1**

    - **JG** Jump if Greater

        effectue un saut si **ZF=0 et SF=OF**

    - **JLE** Jump if Lower or Equal

        effectue un saut si **ZF=1 ou SF différent de OF**

    - **JNE** Jump if Not Equal

        effectue un saut si **ZF=0**

## Stack

→ lifo (Last Input, First Output)

si >6 arg alors a partir du 7e ils sont mis sur la stack

Registers that points to stack :

- **RBP** is the base pointer register. It points to the **base of the current stack frame**.
- **RSP** is the stack pointer, which points to the **top of current stack frame**.

    The stack pointer rsp **must be aligned to a 16-byte boundary** before making a call. Fine, but the process of making a call pushes the return address (8 bytes) on the stack, so when a function gets control, rsp is not aligned. You have to make that extra space yourself, by pushing something or subtracting 8 from rsp.

Commands for working with stack :

- `push argument` - increments stack pointer (RSP) and stores argument in location pointed by stack pointer
- `pop argument` - copied data to argument from location pointed by stack pointer

## Set d'instructions

liste de toutes les instructions : https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-instruction-set-reference-manual-325383.pdf

Une instruction est faite d'un byte ou 8 bits, les 4 premiers représentent l'action a effectuer et les 4 suivants representent l'emplacement mémoire d'ou effectuer l'action

Syntaxe : `instruction source` ou `instruction destination source`

Types de l’opérande `source`

- registre
- mémoire
- immédiat, valeur codée dans l’instruction
- implicite, valeur qui n’apparait pas dans l’instruction

Types de l’opérande `destination`

- registre
- mémoire

**ATTENTION** : Une instruction ne peut pas avoir deux opérandes de type mémoire.

**[cetteAdresse]** représente la valeur stockée a l’adresse cette adresse.

**[ceRegistre]** represente la valeur stockée **a l’adresse contenue dans le registre**

On peut associer une étiquette cetteEtiquette a une adresse mémoire et utiliser [cetteEtiquette]

`call *processus`* permet d'appeler un processus/une fonction externe et stocke dans l'***instruction pointer*** l'adresse de la prochaine instruction

`ret` permet de retourner a l'adresse stockee dans le RIP = registre instruction pointer donc de poursuivre le programme au niveau de ca

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/233684d4-1d93-42a8-b669-bb7e1884864a/Untitled.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/233684d4-1d93-42a8-b669-bb7e1884864a/Untitled.png)

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/589fa91e-9b00-43ec-947a-1acdefbc2903/Untitled.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/589fa91e-9b00-43ec-947a-1acdefbc2903/Untitled.png)

**Les Instructions ET la data sont stockees dans la meme memoire !** Au final ce ne sont que des nombres binaires

## NASM

Netwide Assembler est un **assembleur** utilisant la syntaxe Intel pour du 16, 32, 64 et 86 bit.

```jsx
//pour verifier que nasm est installé sur ordi 
whereis nasm
//connaitre son architecture : x64 ou autre 
uname -a
//Compile w/ nasm. macho64 is the format of modern macOS executables 
**nasm -f macho64 fileName.asm -o oName.o//avec start sans _**
//if file contains start
**ld -o exeName -e start oName.o -macosx_version_min 10.15 -static**

//si file contient main
gcc test.o -o test
//Executer
./test ou ./a.out
```

autres commandes : `nasm -f macho64 fileName.s -o oName.o && ld oName.o -o exeName`

```
//2 ways of defining string in nasm
db 'Hello world', 10 ; with single quotes
db "Hello world", 10 ; with double quotes
//length of a string
message db  'hello, world'
msglen  equ $-message
// $ pointe sur la position actuelle donc la fin de la string et message pointe sur le debut de la string
```

### Structure of NASM program

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/93034ce5-16cf-4746-9483-02997ec797ff/Untitled.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/93034ce5-16cf-4746-9483-02997ec797ff/Untitled.png)

The fundamental data types are bytes, words, doublewords, quadwords, and double quadwords. **A byte is eight bits**, a **word is 2 bytes**, a doubleword is 4 bytes, a quadword is 8 bytes and a double quadword is 16 bytes (128 bits)

- `data` - section is used for declaring initialized data or **constants**
    - **DB**, DW, DD, DQ, DT, DO, DY and DZ - are used for declaring initialized data, respectively bytes, word, double, quad, double quads....
    - uninitialized counterparts RESB, RESW, RESD, RESQ, REST, RESO, RESY and RESZ;
    - EQU - defines constant

- `bss` - section is used for declaring non initialized variables / The .bss section is for **writable data.**
- `text` - section is used for code

there are 16 general-purpose registers - rax, rbx, rcx, rdx, rbp, rsp, rsi, rdi, r8, r9, r10, r11, r12, r13, r14, r15

## Syscalls

— La valeur de retour de l’appel système est placée dans RAX.
— Le système utilise **sa propre pile**, la **pile du processus appelant n’est pas modifiée.**
— Les registres sont inchangés, sauf peut-être RCX et R11.

## Errno / standard errors

[https://docs.freebsd.org/en/books/developers-handbook/x86-return-values.html](https://docs.freebsd.org/en/books/developers-handbook/x86-return-values.html)

fd :

- 0 = standar input
- 1 = standard output
- **2 = standard error**

The **error code** is stored in rax bc if there is no error, there is no error code so the return value can be stored there : if there is an error, there is no return value. One register can contain either.

When using the **standard FreeBSD calling convention**, the **carry flag** is cleared upon success, **set upon failure**.

```
The __error() function returns a pointer to a field in the	thread specific structure for threads other than the	initial	thread.	 
For the initial thread and non-threaded processes, __error() returns a pointer to a globalerrno variable that	is compatible with the previous	definition.
```
