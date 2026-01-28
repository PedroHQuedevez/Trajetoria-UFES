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
  fstore 1
  iconst_0
  istore 0
  iconst_1
  istore 0
  iconst_2
  i2f
  fstore 1
  iconst_0
  iload 0
  if_icmpne L0
  iconst_1
  goto L1
L0:
  iconst_0
L1:
  ifeq L2
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc "O numero "
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  getstatic java/lang/System/out Ljava/io/PrintStream;
  iload 0
  invokestatic java/lang/String/valueOf(Z)Ljava/lang/String;
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc " é False."
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  goto L3
L2:
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc "O numero "
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  getstatic java/lang/System/out Ljava/io/PrintStream;
  iload 0
  invokestatic java/lang/String/valueOf(Z)Ljava/lang/String;
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc " é impar."
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
L3:
  return
.end method
