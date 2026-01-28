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
  istore 2
  iconst_0
  istore 0
  iconst_0
  istore 1
  bipush 10
  istore 0
  iconst_5
  istore 1
  iload 0
  iload 1
  if_icmpgt L0
  iconst_0
  goto L1
L0:
  iconst_1
L1:
  istore 2
  getstatic java/lang/System/out Ljava/io/PrintStream;
  iload 2
  invokestatic java/lang/String/valueOf(Z)Ljava/lang/String;
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  iload 0
  iload 1
  if_icmpgt L2
  iconst_0
  goto L3
L2:
  iconst_1
L3:
  ifeq L4
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc "x é maior que y"
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  goto L5
L4:
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc "x não é maior que y"
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
L5:
  return
.end method
