// Generated from PascalParser.g by ANTLR 4.13.2
package parser;
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link PascalParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface PascalParserVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link PascalParser#program}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgram(PascalParser.ProgramContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#varsSect}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVarsSect(PascalParser.VarsSectContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#varDecl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVarDecl(PascalParser.VarDeclContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#identifierList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIdentifierList(PascalParser.IdentifierListContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#typeSpec}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTypeSpec(PascalParser.TypeSpecContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#arrayType}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArrayType(PascalParser.ArrayTypeContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#indexedVariable}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIndexedVariable(PascalParser.IndexedVariableContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#assignIndexed}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssignIndexed(PascalParser.AssignIndexedContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#range}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRange(PascalParser.RangeContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#stmtSect}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStmtSect(PascalParser.StmtSectContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#stmtList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStmtList(PascalParser.StmtListContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#stmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStmt(PascalParser.StmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#structureStmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStructureStmt(PascalParser.StructureStmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#assignStmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssignStmt(PascalParser.AssignStmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#ifStmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIfStmt(PascalParser.IfStmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#readStmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitReadStmt(PascalParser.ReadStmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#writeStmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitWriteStmt(PascalParser.WriteStmtContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#forStmt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitForStmt(PascalParser.ForStmtContext ctx);
	/**
	 * Visit a parse tree produced by the {@code integerExpr}
	 * labeled alternative in {@link PascalParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIntegerExpr(PascalParser.IntegerExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code booleanExpr}
	 * labeled alternative in {@link PascalParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBooleanExpr(PascalParser.BooleanExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code realExpr}
	 * labeled alternative in {@link PascalParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRealExpr(PascalParser.RealExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code orExpr}
	 * labeled alternative in {@link PascalParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOrExpr(PascalParser.OrExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code parenExpr}
	 * labeled alternative in {@link PascalParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitParenExpr(PascalParser.ParenExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code indexedVariableExpr}
	 * labeled alternative in {@link PascalParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIndexedVariableExpr(PascalParser.IndexedVariableExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code assignIndexedExpr}
	 * labeled alternative in {@link PascalParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssignIndexedExpr(PascalParser.AssignIndexedExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code stringExpr}
	 * labeled alternative in {@link PascalParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStringExpr(PascalParser.StringExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code notExpr}
	 * labeled alternative in {@link PascalParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNotExpr(PascalParser.NotExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code addExpr}
	 * labeled alternative in {@link PascalParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAddExpr(PascalParser.AddExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code functionCallExpr}
	 * labeled alternative in {@link PascalParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionCallExpr(PascalParser.FunctionCallExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code mulExpr}
	 * labeled alternative in {@link PascalParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMulExpr(PascalParser.MulExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code relExpr}
	 * labeled alternative in {@link PascalParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRelExpr(PascalParser.RelExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code identifierExpr}
	 * labeled alternative in {@link PascalParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIdentifierExpr(PascalParser.IdentifierExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code andExpr}
	 * labeled alternative in {@link PascalParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAndExpr(PascalParser.AndExprContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#exprFor}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprFor(PascalParser.ExprForContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#mulop}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMulop(PascalParser.MulopContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#addop}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAddop(PascalParser.AddopContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#relop}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRelop(PascalParser.RelopContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#functionDecl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionDecl(PascalParser.FunctionDeclContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#functionHeading}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionHeading(PascalParser.FunctionHeadingContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#formalParameterList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFormalParameterList(PascalParser.FormalParameterListContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#functionBlock}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionBlock(PascalParser.FunctionBlockContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#functionCall}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionCall(PascalParser.FunctionCallContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#exprList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExprList(PascalParser.ExprListContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#procedureDecl}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProcedureDecl(PascalParser.ProcedureDeclContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#procedureHeading}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProcedureHeading(PascalParser.ProcedureHeadingContext ctx);
	/**
	 * Visit a parse tree produced by {@link PascalParser#procedureBlock}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProcedureBlock(PascalParser.ProcedureBlockContext ctx);
}