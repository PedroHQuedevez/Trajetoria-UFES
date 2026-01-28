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
  fstore 2
  fconst_0
  fstore 0
  fconst_0
  fstore 1
  fconst_0
  fstore 3
  iconst_2
  i2f
  fstore 0
  iconst_3
  i2f
  fstore 1
  iconst_0
  fstore 2
  getstatic java/lang/System/out Ljava/io/PrintStream;
  fload 2
  invokestatic java/lang/String/valueOf(F)Ljava/lang/String;
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  return
.end method
