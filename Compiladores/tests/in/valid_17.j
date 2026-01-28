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
  iconst_0
  istore 0
  iconst_5
  istore 0
  iload 0
  iconst_1
  if_icmplt L0
  iconst_0
  goto L1
L0:
  iconst_1
L1:
  ifeq L2
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc "Numero invalido. Digite um valor maior ou igual a 1."
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  goto L3
L2:
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc "Contando de 1 ate "
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  getstatic java/lang/System/out Ljava/io/PrintStream;
  iload 0
  invokestatic java/lang/String/valueOf(I)Ljava/lang/String;
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc ":"
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  iconst_0
L3:
  return
.end method
