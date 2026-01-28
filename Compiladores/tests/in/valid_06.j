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
  iconst_0
  istore 1
  iconst_1
  istore 1
  bipush 10
  istore 2
L0:
  iload 1
  iload 2
  if_icmpgt L1
  iload 1
  iconst_2
  imul
  iload 1
  iconst_1
  iadd
  istore 1
  goto L0
L1:
  getstatic java/lang/System/out Ljava/io/PrintStream;
  invokestatic java/lang/String/valueOf(I)Ljava/lang/String;
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  return
.end method
