.class public PascalProgram
.super java/lang/Object

.method public <init>()V
  aload_0
  invokespecial java/lang/Object/<init>()V
  return
.end method

.method public static main([Ljava/lang/String;)V
  .limit stack 10
  .limit locals 10
  fconst_0
  fstore 3
  iconst_0
  istore 0
  iconst_0
  istore 1
  iconst_0
  istore 2
  bipush 20
  istore 0
  iconst_3
  istore 1
  iload 0
  iload 1
  isub
  istore 2
  iload 0
  iload 1
  fdiv
  fstore 3
  getstatic java/lang/System/out Ljava/io/PrintStream;
  iload 2
  invokestatic java/lang/String/valueOf(I)Ljava/lang/String;
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  getstatic java/lang/System/out Ljava/io/PrintStream;
  fload 3
  invokestatic java/lang/String/valueOf(F)Ljava/lang/String;
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  iload 0
  iload 1
  if_icmpgt L0
  iconst_0
  goto L1
L0:
  iconst_1
L1:
  ifeq L2
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc "verdadeiro"
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  goto L3
L2:
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc "falso"
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
L3:
  return
.end method
