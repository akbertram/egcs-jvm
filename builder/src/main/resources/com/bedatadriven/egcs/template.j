.class public Prog
.super com/bedatadriven/egcs/runtime/CObject

.method public <init>()V
        .limit stack 5
        .limit locals 16

        aload_0
        invokenonvirtual com/bedatadriven/egcs/runtime/CObject/<init>()V
        return
.end method

.method public static main([Ljava/lang/String;)V
        .limit stack 5
        .limit locals 16 
        
        new Prog
        dup
        invokespecial Prog/<init>()V
        aload_0  
        invokevirtual Prog/Realmain([Ljava/lang/String;)V
        return 
.end method


.method name()Ljava/lang/String;
	.limit locals 2
	.limit stack 3

	ldc	"Prog"
	areturn
.end method

.method datanames()[Ljava/lang/String;
	.limit locals 2
	.limit stack 3

	iconst_0
	anewarray	java/lang/String
	areturn
.end method

.method datasizes()[I
	.limit locals 2
	.limit stack 3

	iconst_0
	newarray	 int
	areturn
.end method

.method datastarts()[I
	.limit locals 2
	.limit stack 3

	iconst_0
	newarray	int
	areturn
.end method
