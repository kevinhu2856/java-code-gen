class example
{
field static int a
/* 1: int a; */
method public static int add(int, int)
max_locals 15
max_stack 15
{
/* 2: int add (int a, int b) */
/* 3: { */
iload 0
iload 1
iadd
ireturn
/* 4: return a+b; */
}
/* 5: } */
/* 6: */
method public static void main(java.lang.String[])
max_locals 15
max_stack 15
{
/* 7: main() */
/* 8: { */
/* 9: int c; */
sipush 5
putstatic int example.a
/* 10: a = 5; */
getstatic int example.a
sipush 10
invokestatic int example.add(int, int)
istore 0
/* 11: c = add(a, 10); */
iload 0
sipush 10
isub
ifgt L0
iconst_0
goto L1
L0:
iconst_1
L1:
10
ifeq L2
/* 12: if (c > 10) */
getstatic java.io.PrintStream java.lang.System.out
iload 0
ineg
invokevirtual void java.io.PrintStream.print(int)
/* 13: print -c; */
goto L3
L2:
/* 14: else */
getstatic java.io.PrintStream java.lang.System.out
iload 0
invokevirtual void java.io.PrintStream.print(int)
L3:
/* 15: print c; */
getstatic java.io.PrintStream java.lang.System.out
ldc "Hello World"
invokevirtual void java.io.PrintStream.println(java.lang.String)
/* 16: println "Hello World"; */
return
}
/* 17: } */
}
