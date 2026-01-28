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
  fstore 0
  bipush 6
  i2f
  fstore 0
  fload 0
  iconst_0
  if_icmpge L0
  iconst_0
  goto L1
L0:
  iconst_1
L1:
  fload 0
  bipush 10
  if_icmple L2
  iconst_0
  goto L3
L2:
  iconst_1
L3:
  iand
  ifeq L4
  fload 0
  bipush 7
  if_icmpge L6
  iconst_0
  goto L7
L6:
  iconst_1
L7:
  ifeq L8
  fload 0
  bipush 9
  if_icmpge L10
  iconst_0
  goto L11
L10:
  iconst_1
L11:
  ifeq L12
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc "Excelente!"
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  goto L13
L12:
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc "Aprovado com bom desempenho."
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
L13:
  goto L9
L8:
  fload 0
  iconst_5
  if_icmpge L14
  iconst_0
  goto L15
L14:
  iconst_1
L15:
  ifeq L16
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc "Recuperação."
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
  goto L17
L16:
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc "Reprovado."
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
L17:
L9:
  goto L5
L4:
  getstatic java/lang/System/out Ljava/io/PrintStream;
  ldc "Nota inválida. Digite um valor entre 0 e 10."
  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
L5:
  return
.end method
