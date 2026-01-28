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
  bipush 10
  istore 0
  getstatic java/lang/System/out Ljava/io/PrintStream;
  iload 0
  invokestatic java/lang/String/valueOf(I)Ljava/lang/String;
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  return
.end method
