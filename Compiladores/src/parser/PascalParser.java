// Generated from PascalParser.g by ANTLR 4.13.2
package parser;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class PascalParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		ASSIGN=1, EQUAL=2, LESS=3, GREATER=4, LE=5, GE=6, NE=7, PLUS=8, MINUS=9, 
		STAR=10, SLASH=11, LPAREN=12, RPAREN=13, LBRACK=14, RBRACK=15, COMMA=16, 
		COLON=17, SEMICOLON=18, DOT=19, DOTDOT=20, POINTER_REF=21, AND=22, ARRAY=23, 
		BEGIN=24, BOOLEAN=25, CASE=26, CHAR=27, CONST=28, DIV=29, DO=30, DOWNTO=31, 
		ELSE=32, END=33, FILE=34, FOR=35, FUNCTION=36, GOTO=37, IF=38, IN=39, 
		INTEGER=40, LABEL=41, MOD=42, NIL=43, NOT=44, OF=45, OR=46, PACKED=47, 
		PROCEDURE=48, PROGRAM=49, READ=50, REAL=51, RECORD=52, REPEAT=53, SET=54, 
		STRING=55, THEN=56, TO=57, TYPE=58, UNTIL=59, VAR=60, WHILE=61, WITH=62, 
		WRITE=63, READ_LN=64, WRITE_LN=65, INTEGER_VALUE=66, REAL_VALUE=67, BOOLEAN_VALUE=68, 
		STRING_VALUE=69, IDENTIFIER=70, WS=71, COMMENT=72, LINE_COMMENT=73;
	public static final int
		RULE_program = 0, RULE_varsSect = 1, RULE_varDecl = 2, RULE_identifierList = 3, 
		RULE_typeSpec = 4, RULE_arrayType = 5, RULE_indexedVariable = 6, RULE_assignIndexed = 7, 
		RULE_range = 8, RULE_stmtSect = 9, RULE_stmtList = 10, RULE_stmt = 11, 
		RULE_structureStmt = 12, RULE_assignStmt = 13, RULE_ifStmt = 14, RULE_readStmt = 15, 
		RULE_writeStmt = 16, RULE_forStmt = 17, RULE_expr = 18, RULE_exprFor = 19, 
		RULE_mulop = 20, RULE_addop = 21, RULE_relop = 22, RULE_functionDecl = 23, 
		RULE_functionHeading = 24, RULE_formalParameterList = 25, RULE_functionBlock = 26, 
		RULE_functionCall = 27, RULE_exprList = 28, RULE_procedureDecl = 29, RULE_procedureHeading = 30, 
		RULE_procedureBlock = 31;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "varsSect", "varDecl", "identifierList", "typeSpec", "arrayType", 
			"indexedVariable", "assignIndexed", "range", "stmtSect", "stmtList", 
			"stmt", "structureStmt", "assignStmt", "ifStmt", "readStmt", "writeStmt", 
			"forStmt", "expr", "exprFor", "mulop", "addop", "relop", "functionDecl", 
			"functionHeading", "formalParameterList", "functionBlock", "functionCall", 
			"exprList", "procedureDecl", "procedureHeading", "procedureBlock"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "':='", "'='", "'<'", "'>'", "'<='", "'>='", "'<>'", "'+'", "'-'", 
			"'*'", "'/'", "'('", "')'", null, null, "','", "':'", "';'", "'.'", "'..'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "ASSIGN", "EQUAL", "LESS", "GREATER", "LE", "GE", "NE", "PLUS", 
			"MINUS", "STAR", "SLASH", "LPAREN", "RPAREN", "LBRACK", "RBRACK", "COMMA", 
			"COLON", "SEMICOLON", "DOT", "DOTDOT", "POINTER_REF", "AND", "ARRAY", 
			"BEGIN", "BOOLEAN", "CASE", "CHAR", "CONST", "DIV", "DO", "DOWNTO", "ELSE", 
			"END", "FILE", "FOR", "FUNCTION", "GOTO", "IF", "IN", "INTEGER", "LABEL", 
			"MOD", "NIL", "NOT", "OF", "OR", "PACKED", "PROCEDURE", "PROGRAM", "READ", 
			"REAL", "RECORD", "REPEAT", "SET", "STRING", "THEN", "TO", "TYPE", "UNTIL", 
			"VAR", "WHILE", "WITH", "WRITE", "READ_LN", "WRITE_LN", "INTEGER_VALUE", 
			"REAL_VALUE", "BOOLEAN_VALUE", "STRING_VALUE", "IDENTIFIER", "WS", "COMMENT", 
			"LINE_COMMENT"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "PascalParser.g"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public PascalParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProgramContext extends ParserRuleContext {
		public TerminalNode PROGRAM() { return getToken(PascalParser.PROGRAM, 0); }
		public TerminalNode IDENTIFIER() { return getToken(PascalParser.IDENTIFIER, 0); }
		public TerminalNode SEMICOLON() { return getToken(PascalParser.SEMICOLON, 0); }
		public StmtSectContext stmtSect() {
			return getRuleContext(StmtSectContext.class,0);
		}
		public TerminalNode DOT() { return getToken(PascalParser.DOT, 0); }
		public TerminalNode EOF() { return getToken(PascalParser.EOF, 0); }
		public VarsSectContext varsSect() {
			return getRuleContext(VarsSectContext.class,0);
		}
		public List<FunctionDeclContext> functionDecl() {
			return getRuleContexts(FunctionDeclContext.class);
		}
		public FunctionDeclContext functionDecl(int i) {
			return getRuleContext(FunctionDeclContext.class,i);
		}
		public List<ProcedureDeclContext> procedureDecl() {
			return getRuleContexts(ProcedureDeclContext.class);
		}
		public ProcedureDeclContext procedureDecl(int i) {
			return getRuleContext(ProcedureDeclContext.class,i);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitProgram(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(64);
			match(PROGRAM);
			setState(65);
			match(IDENTIFIER);
			setState(66);
			match(SEMICOLON);
			setState(68);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==VAR) {
				{
				setState(67);
				varsSect();
				}
			}

			setState(73);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==FUNCTION) {
				{
				{
				setState(70);
				functionDecl();
				}
				}
				setState(75);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(79);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==PROCEDURE) {
				{
				{
				setState(76);
				procedureDecl();
				}
				}
				setState(81);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(82);
			stmtSect();
			setState(83);
			match(DOT);
			setState(84);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class VarsSectContext extends ParserRuleContext {
		public TerminalNode VAR() { return getToken(PascalParser.VAR, 0); }
		public List<VarDeclContext> varDecl() {
			return getRuleContexts(VarDeclContext.class);
		}
		public VarDeclContext varDecl(int i) {
			return getRuleContext(VarDeclContext.class,i);
		}
		public VarsSectContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_varsSect; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitVarsSect(this);
			else return visitor.visitChildren(this);
		}
	}

	public final VarsSectContext varsSect() throws RecognitionException {
		VarsSectContext _localctx = new VarsSectContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_varsSect);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(86);
			match(VAR);
			setState(90);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==IDENTIFIER) {
				{
				{
				setState(87);
				varDecl();
				}
				}
				setState(92);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class VarDeclContext extends ParserRuleContext {
		public IdentifierListContext identifierList() {
			return getRuleContext(IdentifierListContext.class,0);
		}
		public TerminalNode COLON() { return getToken(PascalParser.COLON, 0); }
		public TypeSpecContext typeSpec() {
			return getRuleContext(TypeSpecContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(PascalParser.SEMICOLON, 0); }
		public VarDeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_varDecl; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitVarDecl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final VarDeclContext varDecl() throws RecognitionException {
		VarDeclContext _localctx = new VarDeclContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_varDecl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(93);
			identifierList();
			setState(94);
			match(COLON);
			setState(95);
			typeSpec();
			setState(96);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IdentifierListContext extends ParserRuleContext {
		public List<TerminalNode> IDENTIFIER() { return getTokens(PascalParser.IDENTIFIER); }
		public TerminalNode IDENTIFIER(int i) {
			return getToken(PascalParser.IDENTIFIER, i);
		}
		public List<TerminalNode> COMMA() { return getTokens(PascalParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(PascalParser.COMMA, i);
		}
		public IdentifierListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_identifierList; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitIdentifierList(this);
			else return visitor.visitChildren(this);
		}
	}

	public final IdentifierListContext identifierList() throws RecognitionException {
		IdentifierListContext _localctx = new IdentifierListContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_identifierList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(98);
			match(IDENTIFIER);
			setState(103);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(99);
				match(COMMA);
				setState(100);
				match(IDENTIFIER);
				}
				}
				setState(105);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TypeSpecContext extends ParserRuleContext {
		public TerminalNode BOOLEAN() { return getToken(PascalParser.BOOLEAN, 0); }
		public TerminalNode INTEGER() { return getToken(PascalParser.INTEGER, 0); }
		public TerminalNode REAL() { return getToken(PascalParser.REAL, 0); }
		public TerminalNode STRING() { return getToken(PascalParser.STRING, 0); }
		public ArrayTypeContext arrayType() {
			return getRuleContext(ArrayTypeContext.class,0);
		}
		public TypeSpecContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typeSpec; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitTypeSpec(this);
			else return visitor.visitChildren(this);
		}
	}

	public final TypeSpecContext typeSpec() throws RecognitionException {
		TypeSpecContext _localctx = new TypeSpecContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_typeSpec);
		try {
			setState(111);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case BOOLEAN:
				enterOuterAlt(_localctx, 1);
				{
				setState(106);
				match(BOOLEAN);
				}
				break;
			case INTEGER:
				enterOuterAlt(_localctx, 2);
				{
				setState(107);
				match(INTEGER);
				}
				break;
			case REAL:
				enterOuterAlt(_localctx, 3);
				{
				setState(108);
				match(REAL);
				}
				break;
			case STRING:
				enterOuterAlt(_localctx, 4);
				{
				setState(109);
				match(STRING);
				}
				break;
			case ARRAY:
				enterOuterAlt(_localctx, 5);
				{
				setState(110);
				arrayType();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ArrayTypeContext extends ParserRuleContext {
		public TerminalNode ARRAY() { return getToken(PascalParser.ARRAY, 0); }
		public TerminalNode LBRACK() { return getToken(PascalParser.LBRACK, 0); }
		public RangeContext range() {
			return getRuleContext(RangeContext.class,0);
		}
		public TerminalNode RBRACK() { return getToken(PascalParser.RBRACK, 0); }
		public TerminalNode OF() { return getToken(PascalParser.OF, 0); }
		public TypeSpecContext typeSpec() {
			return getRuleContext(TypeSpecContext.class,0);
		}
		public ArrayTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arrayType; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitArrayType(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ArrayTypeContext arrayType() throws RecognitionException {
		ArrayTypeContext _localctx = new ArrayTypeContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_arrayType);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(113);
			match(ARRAY);
			setState(114);
			match(LBRACK);
			setState(115);
			range();
			setState(116);
			match(RBRACK);
			setState(117);
			match(OF);
			setState(118);
			typeSpec();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IndexedVariableContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(PascalParser.IDENTIFIER, 0); }
		public TerminalNode LBRACK() { return getToken(PascalParser.LBRACK, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode RBRACK() { return getToken(PascalParser.RBRACK, 0); }
		public IndexedVariableContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_indexedVariable; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitIndexedVariable(this);
			else return visitor.visitChildren(this);
		}
	}

	public final IndexedVariableContext indexedVariable() throws RecognitionException {
		IndexedVariableContext _localctx = new IndexedVariableContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_indexedVariable);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(120);
			match(IDENTIFIER);
			setState(121);
			match(LBRACK);
			setState(122);
			expr(0);
			setState(126);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (((((_la - 12)) & ~0x3f) == 0 && ((1L << (_la - 12)) & 558446358088908801L) != 0)) {
				{
				{
				setState(123);
				expr(0);
				}
				}
				setState(128);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(129);
			match(RBRACK);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AssignIndexedContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(PascalParser.IDENTIFIER, 0); }
		public TerminalNode LBRACK() { return getToken(PascalParser.LBRACK, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode RBRACK() { return getToken(PascalParser.RBRACK, 0); }
		public TerminalNode ASSIGN() { return getToken(PascalParser.ASSIGN, 0); }
		public AssignIndexedContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assignIndexed; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitAssignIndexed(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AssignIndexedContext assignIndexed() throws RecognitionException {
		AssignIndexedContext _localctx = new AssignIndexedContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_assignIndexed);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(131);
			match(IDENTIFIER);
			setState(132);
			match(LBRACK);
			setState(133);
			expr(0);
			setState(137);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (((((_la - 12)) & ~0x3f) == 0 && ((1L << (_la - 12)) & 558446358088908801L) != 0)) {
				{
				{
				setState(134);
				expr(0);
				}
				}
				setState(139);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(140);
			match(RBRACK);
			setState(141);
			match(ASSIGN);
			setState(142);
			expr(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RangeContext extends ParserRuleContext {
		public List<TerminalNode> INTEGER_VALUE() { return getTokens(PascalParser.INTEGER_VALUE); }
		public TerminalNode INTEGER_VALUE(int i) {
			return getToken(PascalParser.INTEGER_VALUE, i);
		}
		public TerminalNode DOTDOT() { return getToken(PascalParser.DOTDOT, 0); }
		public RangeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_range; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitRange(this);
			else return visitor.visitChildren(this);
		}
	}

	public final RangeContext range() throws RecognitionException {
		RangeContext _localctx = new RangeContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_range);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(144);
			match(INTEGER_VALUE);
			setState(145);
			match(DOTDOT);
			setState(146);
			match(INTEGER_VALUE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StmtSectContext extends ParserRuleContext {
		public TerminalNode BEGIN() { return getToken(PascalParser.BEGIN, 0); }
		public StmtListContext stmtList() {
			return getRuleContext(StmtListContext.class,0);
		}
		public TerminalNode END() { return getToken(PascalParser.END, 0); }
		public StmtSectContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmtSect; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitStmtSect(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StmtSectContext stmtSect() throws RecognitionException {
		StmtSectContext _localctx = new StmtSectContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_stmtSect);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(148);
			match(BEGIN);
			setState(149);
			stmtList();
			setState(150);
			match(END);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StmtListContext extends ParserRuleContext {
		public List<StmtContext> stmt() {
			return getRuleContexts(StmtContext.class);
		}
		public StmtContext stmt(int i) {
			return getRuleContext(StmtContext.class,i);
		}
		public List<TerminalNode> SEMICOLON() { return getTokens(PascalParser.SEMICOLON); }
		public TerminalNode SEMICOLON(int i) {
			return getToken(PascalParser.SEMICOLON, i);
		}
		public StmtListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmtList; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitStmtList(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StmtListContext stmtList() throws RecognitionException {
		StmtListContext _localctx = new StmtListContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_stmtList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(157);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (((((_la - 24)) & ~0x3f) == 0 && ((1L << (_la - 24)) & 74217102002177L) != 0)) {
				{
				{
				setState(152);
				stmt();
				setState(153);
				match(SEMICOLON);
				}
				}
				setState(159);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StmtContext extends ParserRuleContext {
		public AssignStmtContext assignStmt() {
			return getRuleContext(AssignStmtContext.class,0);
		}
		public IfStmtContext ifStmt() {
			return getRuleContext(IfStmtContext.class,0);
		}
		public ReadStmtContext readStmt() {
			return getRuleContext(ReadStmtContext.class,0);
		}
		public WriteStmtContext writeStmt() {
			return getRuleContext(WriteStmtContext.class,0);
		}
		public StructureStmtContext structureStmt() {
			return getRuleContext(StructureStmtContext.class,0);
		}
		public ForStmtContext forStmt() {
			return getRuleContext(ForStmtContext.class,0);
		}
		public FunctionCallContext functionCall() {
			return getRuleContext(FunctionCallContext.class,0);
		}
		public StmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitStmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StmtContext stmt() throws RecognitionException {
		StmtContext _localctx = new StmtContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_stmt);
		try {
			setState(167);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,9,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(160);
				assignStmt();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(161);
				ifStmt();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(162);
				readStmt();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(163);
				writeStmt();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(164);
				structureStmt();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(165);
				forStmt();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(166);
				functionCall();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StructureStmtContext extends ParserRuleContext {
		public TerminalNode BEGIN() { return getToken(PascalParser.BEGIN, 0); }
		public StmtListContext stmtList() {
			return getRuleContext(StmtListContext.class,0);
		}
		public TerminalNode END() { return getToken(PascalParser.END, 0); }
		public StructureStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_structureStmt; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitStructureStmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StructureStmtContext structureStmt() throws RecognitionException {
		StructureStmtContext _localctx = new StructureStmtContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_structureStmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(169);
			match(BEGIN);
			setState(170);
			stmtList();
			setState(171);
			match(END);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AssignStmtContext extends ParserRuleContext {
		public TerminalNode ASSIGN() { return getToken(PascalParser.ASSIGN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(PascalParser.IDENTIFIER, 0); }
		public IndexedVariableContext indexedVariable() {
			return getRuleContext(IndexedVariableContext.class,0);
		}
		public AssignStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assignStmt; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitAssignStmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AssignStmtContext assignStmt() throws RecognitionException {
		AssignStmtContext _localctx = new AssignStmtContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_assignStmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(175);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,10,_ctx) ) {
			case 1:
				{
				setState(173);
				match(IDENTIFIER);
				}
				break;
			case 2:
				{
				setState(174);
				indexedVariable();
				}
				break;
			}
			setState(177);
			match(ASSIGN);
			setState(178);
			expr(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IfStmtContext extends ParserRuleContext {
		public TerminalNode IF() { return getToken(PascalParser.IF, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode THEN() { return getToken(PascalParser.THEN, 0); }
		public List<StmtContext> stmt() {
			return getRuleContexts(StmtContext.class);
		}
		public StmtContext stmt(int i) {
			return getRuleContext(StmtContext.class,i);
		}
		public List<StructureStmtContext> structureStmt() {
			return getRuleContexts(StructureStmtContext.class);
		}
		public StructureStmtContext structureStmt(int i) {
			return getRuleContext(StructureStmtContext.class,i);
		}
		public TerminalNode ELSE() { return getToken(PascalParser.ELSE, 0); }
		public IfStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ifStmt; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitIfStmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final IfStmtContext ifStmt() throws RecognitionException {
		IfStmtContext _localctx = new IfStmtContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_ifStmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(180);
			match(IF);
			setState(181);
			expr(0);
			setState(182);
			match(THEN);
			setState(185);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,11,_ctx) ) {
			case 1:
				{
				setState(183);
				stmt();
				}
				break;
			case 2:
				{
				setState(184);
				structureStmt();
				}
				break;
			}
			setState(192);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,13,_ctx) ) {
			case 1:
				{
				setState(187);
				match(ELSE);
				setState(190);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
				case 1:
					{
					setState(188);
					stmt();
					}
					break;
				case 2:
					{
					setState(189);
					structureStmt();
					}
					break;
				}
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ReadStmtContext extends ParserRuleContext {
		public TerminalNode READ_LN() { return getToken(PascalParser.READ_LN, 0); }
		public TerminalNode LPAREN() { return getToken(PascalParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(PascalParser.RPAREN, 0); }
		public TerminalNode IDENTIFIER() { return getToken(PascalParser.IDENTIFIER, 0); }
		public TerminalNode READ() { return getToken(PascalParser.READ, 0); }
		public ReadStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_readStmt; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitReadStmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ReadStmtContext readStmt() throws RecognitionException {
		ReadStmtContext _localctx = new ReadStmtContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_readStmt);
		int _la;
		try {
			setState(210);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case READ_LN:
				enterOuterAlt(_localctx, 1);
				{
				setState(194);
				match(READ_LN);
				setState(200);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==LPAREN) {
					{
					setState(195);
					match(LPAREN);
					setState(197);
					_errHandler.sync(this);
					_la = _input.LA(1);
					if (_la==IDENTIFIER) {
						{
						setState(196);
						match(IDENTIFIER);
						}
					}

					setState(199);
					match(RPAREN);
					}
				}

				}
				break;
			case READ:
				enterOuterAlt(_localctx, 2);
				{
				setState(202);
				match(READ);
				setState(208);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==LPAREN) {
					{
					setState(203);
					match(LPAREN);
					setState(205);
					_errHandler.sync(this);
					_la = _input.LA(1);
					if (_la==IDENTIFIER) {
						{
						setState(204);
						match(IDENTIFIER);
						}
					}

					setState(207);
					match(RPAREN);
					}
				}

				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class WriteStmtContext extends ParserRuleContext {
		public TerminalNode WRITE_LN() { return getToken(PascalParser.WRITE_LN, 0); }
		public TerminalNode LPAREN() { return getToken(PascalParser.LPAREN, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode RPAREN() { return getToken(PascalParser.RPAREN, 0); }
		public List<TerminalNode> COMMA() { return getTokens(PascalParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(PascalParser.COMMA, i);
		}
		public TerminalNode WRITE() { return getToken(PascalParser.WRITE, 0); }
		public WriteStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_writeStmt; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitWriteStmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final WriteStmtContext writeStmt() throws RecognitionException {
		WriteStmtContext _localctx = new WriteStmtContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_writeStmt);
		int _la;
		try {
			setState(236);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case WRITE_LN:
				enterOuterAlt(_localctx, 1);
				{
				setState(212);
				match(WRITE_LN);
				setState(213);
				match(LPAREN);
				setState(214);
				expr(0);
				setState(219);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==COMMA) {
					{
					{
					setState(215);
					match(COMMA);
					setState(216);
					expr(0);
					}
					}
					setState(221);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(222);
				match(RPAREN);
				}
				break;
			case WRITE:
				enterOuterAlt(_localctx, 2);
				{
				setState(224);
				match(WRITE);
				setState(225);
				match(LPAREN);
				setState(226);
				expr(0);
				setState(231);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==COMMA) {
					{
					{
					setState(227);
					match(COMMA);
					setState(228);
					expr(0);
					}
					}
					setState(233);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(234);
				match(RPAREN);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ForStmtContext extends ParserRuleContext {
		public TerminalNode FOR() { return getToken(PascalParser.FOR, 0); }
		public TerminalNode IDENTIFIER() { return getToken(PascalParser.IDENTIFIER, 0); }
		public TerminalNode ASSIGN() { return getToken(PascalParser.ASSIGN, 0); }
		public List<ExprForContext> exprFor() {
			return getRuleContexts(ExprForContext.class);
		}
		public ExprForContext exprFor(int i) {
			return getRuleContext(ExprForContext.class,i);
		}
		public TerminalNode DO() { return getToken(PascalParser.DO, 0); }
		public TerminalNode TO() { return getToken(PascalParser.TO, 0); }
		public TerminalNode DOWNTO() { return getToken(PascalParser.DOWNTO, 0); }
		public TerminalNode BEGIN() { return getToken(PascalParser.BEGIN, 0); }
		public StmtContext stmt() {
			return getRuleContext(StmtContext.class,0);
		}
		public TerminalNode END() { return getToken(PascalParser.END, 0); }
		public List<TerminalNode> SEMICOLON() { return getTokens(PascalParser.SEMICOLON); }
		public TerminalNode SEMICOLON(int i) {
			return getToken(PascalParser.SEMICOLON, i);
		}
		public StructureStmtContext structureStmt() {
			return getRuleContext(StructureStmtContext.class,0);
		}
		public ForStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_forStmt; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitForStmt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ForStmtContext forStmt() throws RecognitionException {
		ForStmtContext _localctx = new ForStmtContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_forStmt);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(238);
			match(FOR);
			setState(239);
			match(IDENTIFIER);
			setState(240);
			match(ASSIGN);
			setState(241);
			exprFor();
			setState(242);
			_la = _input.LA(1);
			if ( !(_la==DOWNTO || _la==TO) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(243);
			exprFor();
			setState(244);
			match(DO);
			setState(255);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,23,_ctx) ) {
			case 1:
				{
				setState(245);
				match(BEGIN);
				setState(246);
				stmt();
				setState(248);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==SEMICOLON) {
					{
					setState(247);
					match(SEMICOLON);
					}
				}

				setState(250);
				match(END);
				setState(251);
				match(SEMICOLON);
				}
				break;
			case 2:
				{
				setState(253);
				stmt();
				}
				break;
			case 3:
				{
				setState(254);
				structureStmt();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExprContext extends ParserRuleContext {
		public ExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr; }
	 
		public ExprContext() { }
		public void copyFrom(ExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class IntegerExprContext extends ExprContext {
		public TerminalNode INTEGER_VALUE() { return getToken(PascalParser.INTEGER_VALUE, 0); }
		public IntegerExprContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitIntegerExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class BooleanExprContext extends ExprContext {
		public TerminalNode BOOLEAN_VALUE() { return getToken(PascalParser.BOOLEAN_VALUE, 0); }
		public BooleanExprContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitBooleanExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class RealExprContext extends ExprContext {
		public TerminalNode REAL_VALUE() { return getToken(PascalParser.REAL_VALUE, 0); }
		public RealExprContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitRealExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class OrExprContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode OR() { return getToken(PascalParser.OR, 0); }
		public OrExprContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitOrExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ParenExprContext extends ExprContext {
		public TerminalNode LPAREN() { return getToken(PascalParser.LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(PascalParser.RPAREN, 0); }
		public ParenExprContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitParenExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class IndexedVariableExprContext extends ExprContext {
		public IndexedVariableContext indexedVariable() {
			return getRuleContext(IndexedVariableContext.class,0);
		}
		public IndexedVariableExprContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitIndexedVariableExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class AssignIndexedExprContext extends ExprContext {
		public AssignIndexedContext assignIndexed() {
			return getRuleContext(AssignIndexedContext.class,0);
		}
		public AssignIndexedExprContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitAssignIndexedExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class StringExprContext extends ExprContext {
		public TerminalNode STRING_VALUE() { return getToken(PascalParser.STRING_VALUE, 0); }
		public StringExprContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitStringExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class NotExprContext extends ExprContext {
		public TerminalNode NOT() { return getToken(PascalParser.NOT, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public NotExprContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitNotExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class AddExprContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public AddopContext addop() {
			return getRuleContext(AddopContext.class,0);
		}
		public AddExprContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitAddExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FunctionCallExprContext extends ExprContext {
		public FunctionCallContext functionCall() {
			return getRuleContext(FunctionCallContext.class,0);
		}
		public FunctionCallExprContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitFunctionCallExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class MulExprContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public MulopContext mulop() {
			return getRuleContext(MulopContext.class,0);
		}
		public MulExprContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitMulExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class RelExprContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public RelopContext relop() {
			return getRuleContext(RelopContext.class,0);
		}
		public RelExprContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitRelExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class IdentifierExprContext extends ExprContext {
		public TerminalNode IDENTIFIER() { return getToken(PascalParser.IDENTIFIER, 0); }
		public IdentifierExprContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitIdentifierExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class AndExprContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode AND() { return getToken(PascalParser.AND, 0); }
		public AndExprContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitAndExpr(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExprContext expr() throws RecognitionException {
		return expr(0);
	}

	private ExprContext expr(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ExprContext _localctx = new ExprContext(_ctx, _parentState);
		ExprContext _prevctx = _localctx;
		int _startState = 36;
		enterRecursionRule(_localctx, 36, RULE_expr, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(272);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,24,_ctx) ) {
			case 1:
				{
				_localctx = new NotExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(258);
				match(NOT);
				setState(259);
				expr(10);
				}
				break;
			case 2:
				{
				_localctx = new ParenExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(260);
				match(LPAREN);
				setState(261);
				expr(0);
				setState(262);
				match(RPAREN);
				}
				break;
			case 3:
				{
				_localctx = new BooleanExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(264);
				match(BOOLEAN_VALUE);
				}
				break;
			case 4:
				{
				_localctx = new IntegerExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(265);
				match(INTEGER_VALUE);
				}
				break;
			case 5:
				{
				_localctx = new RealExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(266);
				match(REAL_VALUE);
				}
				break;
			case 6:
				{
				_localctx = new StringExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(267);
				match(STRING_VALUE);
				}
				break;
			case 7:
				{
				_localctx = new IdentifierExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(268);
				match(IDENTIFIER);
				}
				break;
			case 8:
				{
				_localctx = new FunctionCallExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(269);
				functionCall();
				}
				break;
			case 9:
				{
				_localctx = new IndexedVariableExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(270);
				indexedVariable();
				}
				break;
			case 10:
				{
				_localctx = new AssignIndexedExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(271);
				assignIndexed();
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(294);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,26,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(292);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,25,_ctx) ) {
					case 1:
						{
						_localctx = new AndExprContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(274);
						if (!(precpred(_ctx, 15))) throw new FailedPredicateException(this, "precpred(_ctx, 15)");
						setState(275);
						match(AND);
						setState(276);
						expr(16);
						}
						break;
					case 2:
						{
						_localctx = new OrExprContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(277);
						if (!(precpred(_ctx, 14))) throw new FailedPredicateException(this, "precpred(_ctx, 14)");
						setState(278);
						match(OR);
						setState(279);
						expr(15);
						}
						break;
					case 3:
						{
						_localctx = new RelExprContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(280);
						if (!(precpred(_ctx, 13))) throw new FailedPredicateException(this, "precpred(_ctx, 13)");
						setState(281);
						relop();
						setState(282);
						expr(14);
						}
						break;
					case 4:
						{
						_localctx = new AddExprContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(284);
						if (!(precpred(_ctx, 12))) throw new FailedPredicateException(this, "precpred(_ctx, 12)");
						setState(285);
						addop();
						setState(286);
						expr(13);
						}
						break;
					case 5:
						{
						_localctx = new MulExprContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(288);
						if (!(precpred(_ctx, 11))) throw new FailedPredicateException(this, "precpred(_ctx, 11)");
						setState(289);
						mulop();
						setState(290);
						expr(12);
						}
						break;
					}
					} 
				}
				setState(296);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,26,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExprForContext extends ParserRuleContext {
		public TerminalNode INTEGER_VALUE() { return getToken(PascalParser.INTEGER_VALUE, 0); }
		public TerminalNode IDENTIFIER() { return getToken(PascalParser.IDENTIFIER, 0); }
		public ExprForContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exprFor; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitExprFor(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExprForContext exprFor() throws RecognitionException {
		ExprForContext _localctx = new ExprForContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_exprFor);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(297);
			_la = _input.LA(1);
			if ( !(_la==INTEGER_VALUE || _la==IDENTIFIER) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class MulopContext extends ParserRuleContext {
		public TerminalNode STAR() { return getToken(PascalParser.STAR, 0); }
		public TerminalNode SLASH() { return getToken(PascalParser.SLASH, 0); }
		public TerminalNode DIV() { return getToken(PascalParser.DIV, 0); }
		public TerminalNode MOD() { return getToken(PascalParser.MOD, 0); }
		public MulopContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_mulop; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitMulop(this);
			else return visitor.visitChildren(this);
		}
	}

	public final MulopContext mulop() throws RecognitionException {
		MulopContext _localctx = new MulopContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_mulop);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(299);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 4398583385088L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AddopContext extends ParserRuleContext {
		public TerminalNode PLUS() { return getToken(PascalParser.PLUS, 0); }
		public TerminalNode MINUS() { return getToken(PascalParser.MINUS, 0); }
		public AddopContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_addop; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitAddop(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AddopContext addop() throws RecognitionException {
		AddopContext _localctx = new AddopContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_addop);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(301);
			_la = _input.LA(1);
			if ( !(_la==PLUS || _la==MINUS) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RelopContext extends ParserRuleContext {
		public TerminalNode LESS() { return getToken(PascalParser.LESS, 0); }
		public TerminalNode GREATER() { return getToken(PascalParser.GREATER, 0); }
		public TerminalNode LE() { return getToken(PascalParser.LE, 0); }
		public TerminalNode GE() { return getToken(PascalParser.GE, 0); }
		public TerminalNode NE() { return getToken(PascalParser.NE, 0); }
		public TerminalNode EQUAL() { return getToken(PascalParser.EQUAL, 0); }
		public RelopContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_relop; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitRelop(this);
			else return visitor.visitChildren(this);
		}
	}

	public final RelopContext relop() throws RecognitionException {
		RelopContext _localctx = new RelopContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_relop);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(303);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 252L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionDeclContext extends ParserRuleContext {
		public FunctionHeadingContext functionHeading() {
			return getRuleContext(FunctionHeadingContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(PascalParser.SEMICOLON, 0); }
		public FunctionBlockContext functionBlock() {
			return getRuleContext(FunctionBlockContext.class,0);
		}
		public TerminalNode FUNCTION() { return getToken(PascalParser.FUNCTION, 0); }
		public TerminalNode IDENTIFIER() { return getToken(PascalParser.IDENTIFIER, 0); }
		public TerminalNode COLON() { return getToken(PascalParser.COLON, 0); }
		public FunctionDeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionDecl; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitFunctionDecl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FunctionDeclContext functionDecl() throws RecognitionException {
		FunctionDeclContext _localctx = new FunctionDeclContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_functionDecl);
		try {
			setState(313);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,27,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(305);
				functionHeading();
				setState(306);
				match(SEMICOLON);
				setState(307);
				functionBlock();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(309);
				match(FUNCTION);
				setState(310);
				match(IDENTIFIER);
				setState(311);
				match(COLON);
				setState(312);
				functionBlock();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionHeadingContext extends ParserRuleContext {
		public TerminalNode FUNCTION() { return getToken(PascalParser.FUNCTION, 0); }
		public TerminalNode IDENTIFIER() { return getToken(PascalParser.IDENTIFIER, 0); }
		public TerminalNode COLON() { return getToken(PascalParser.COLON, 0); }
		public TypeSpecContext typeSpec() {
			return getRuleContext(TypeSpecContext.class,0);
		}
		public TerminalNode LPAREN() { return getToken(PascalParser.LPAREN, 0); }
		public FormalParameterListContext formalParameterList() {
			return getRuleContext(FormalParameterListContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(PascalParser.RPAREN, 0); }
		public FunctionHeadingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionHeading; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitFunctionHeading(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FunctionHeadingContext functionHeading() throws RecognitionException {
		FunctionHeadingContext _localctx = new FunctionHeadingContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_functionHeading);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(315);
			match(FUNCTION);
			setState(316);
			match(IDENTIFIER);
			setState(321);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LPAREN) {
				{
				setState(317);
				match(LPAREN);
				setState(318);
				formalParameterList();
				setState(319);
				match(RPAREN);
				}
			}

			setState(323);
			match(COLON);
			setState(324);
			typeSpec();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FormalParameterListContext extends ParserRuleContext {
		public List<IdentifierListContext> identifierList() {
			return getRuleContexts(IdentifierListContext.class);
		}
		public IdentifierListContext identifierList(int i) {
			return getRuleContext(IdentifierListContext.class,i);
		}
		public List<TerminalNode> COLON() { return getTokens(PascalParser.COLON); }
		public TerminalNode COLON(int i) {
			return getToken(PascalParser.COLON, i);
		}
		public List<TypeSpecContext> typeSpec() {
			return getRuleContexts(TypeSpecContext.class);
		}
		public TypeSpecContext typeSpec(int i) {
			return getRuleContext(TypeSpecContext.class,i);
		}
		public List<TerminalNode> SEMICOLON() { return getTokens(PascalParser.SEMICOLON); }
		public TerminalNode SEMICOLON(int i) {
			return getToken(PascalParser.SEMICOLON, i);
		}
		public FormalParameterListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_formalParameterList; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitFormalParameterList(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FormalParameterListContext formalParameterList() throws RecognitionException {
		FormalParameterListContext _localctx = new FormalParameterListContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_formalParameterList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(326);
			identifierList();
			setState(327);
			match(COLON);
			setState(328);
			typeSpec();
			setState(336);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SEMICOLON) {
				{
				{
				setState(329);
				match(SEMICOLON);
				setState(330);
				identifierList();
				setState(331);
				match(COLON);
				setState(332);
				typeSpec();
				}
				}
				setState(338);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionBlockContext extends ParserRuleContext {
		public StmtSectContext stmtSect() {
			return getRuleContext(StmtSectContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(PascalParser.SEMICOLON, 0); }
		public VarsSectContext varsSect() {
			return getRuleContext(VarsSectContext.class,0);
		}
		public FunctionBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionBlock; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitFunctionBlock(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FunctionBlockContext functionBlock() throws RecognitionException {
		FunctionBlockContext _localctx = new FunctionBlockContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_functionBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(340);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==VAR) {
				{
				setState(339);
				varsSect();
				}
			}

			setState(342);
			stmtSect();
			setState(343);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionCallContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(PascalParser.IDENTIFIER, 0); }
		public TerminalNode LPAREN() { return getToken(PascalParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(PascalParser.RPAREN, 0); }
		public ExprListContext exprList() {
			return getRuleContext(ExprListContext.class,0);
		}
		public FunctionCallContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionCall; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitFunctionCall(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FunctionCallContext functionCall() throws RecognitionException {
		FunctionCallContext _localctx = new FunctionCallContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_functionCall);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(345);
			match(IDENTIFIER);
			setState(346);
			match(LPAREN);
			setState(348);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (((((_la - 12)) & ~0x3f) == 0 && ((1L << (_la - 12)) & 558446358088908801L) != 0)) {
				{
				setState(347);
				exprList();
				}
			}

			setState(350);
			match(RPAREN);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExprListContext extends ParserRuleContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(PascalParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(PascalParser.COMMA, i);
		}
		public ExprListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exprList; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitExprList(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExprListContext exprList() throws RecognitionException {
		ExprListContext _localctx = new ExprListContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_exprList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(352);
			expr(0);
			setState(357);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(353);
				match(COMMA);
				setState(354);
				expr(0);
				}
				}
				setState(359);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProcedureDeclContext extends ParserRuleContext {
		public ProcedureHeadingContext procedureHeading() {
			return getRuleContext(ProcedureHeadingContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(PascalParser.SEMICOLON, 0); }
		public ProcedureBlockContext procedureBlock() {
			return getRuleContext(ProcedureBlockContext.class,0);
		}
		public TerminalNode PROCEDURE() { return getToken(PascalParser.PROCEDURE, 0); }
		public TerminalNode IDENTIFIER() { return getToken(PascalParser.IDENTIFIER, 0); }
		public TerminalNode COLON() { return getToken(PascalParser.COLON, 0); }
		public ProcedureDeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_procedureDecl; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitProcedureDecl(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ProcedureDeclContext procedureDecl() throws RecognitionException {
		ProcedureDeclContext _localctx = new ProcedureDeclContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_procedureDecl);
		try {
			setState(368);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,33,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(360);
				procedureHeading();
				setState(361);
				match(SEMICOLON);
				setState(362);
				procedureBlock();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(364);
				match(PROCEDURE);
				setState(365);
				match(IDENTIFIER);
				setState(366);
				match(COLON);
				setState(367);
				procedureBlock();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProcedureHeadingContext extends ParserRuleContext {
		public TerminalNode PROCEDURE() { return getToken(PascalParser.PROCEDURE, 0); }
		public TerminalNode IDENTIFIER() { return getToken(PascalParser.IDENTIFIER, 0); }
		public TerminalNode LPAREN() { return getToken(PascalParser.LPAREN, 0); }
		public FormalParameterListContext formalParameterList() {
			return getRuleContext(FormalParameterListContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(PascalParser.RPAREN, 0); }
		public ProcedureHeadingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_procedureHeading; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitProcedureHeading(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ProcedureHeadingContext procedureHeading() throws RecognitionException {
		ProcedureHeadingContext _localctx = new ProcedureHeadingContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_procedureHeading);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(370);
			match(PROCEDURE);
			setState(371);
			match(IDENTIFIER);
			setState(376);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LPAREN) {
				{
				setState(372);
				match(LPAREN);
				setState(373);
				formalParameterList();
				setState(374);
				match(RPAREN);
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProcedureBlockContext extends ParserRuleContext {
		public StmtSectContext stmtSect() {
			return getRuleContext(StmtSectContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(PascalParser.SEMICOLON, 0); }
		public VarsSectContext varsSect() {
			return getRuleContext(VarsSectContext.class,0);
		}
		public ProcedureBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_procedureBlock; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof PascalParserVisitor ) return ((PascalParserVisitor<? extends T>)visitor).visitProcedureBlock(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ProcedureBlockContext procedureBlock() throws RecognitionException {
		ProcedureBlockContext _localctx = new ProcedureBlockContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_procedureBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(379);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==VAR) {
				{
				setState(378);
				varsSect();
				}
			}

			setState(381);
			stmtSect();
			setState(382);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 18:
			return expr_sempred((ExprContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean expr_sempred(ExprContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 15);
		case 1:
			return precpred(_ctx, 14);
		case 2:
			return precpred(_ctx, 13);
		case 3:
			return precpred(_ctx, 12);
		case 4:
			return precpred(_ctx, 11);
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u0001I\u0181\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002"+
		"\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007\u000f"+
		"\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007\u0012"+
		"\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002\u0015\u0007\u0015"+
		"\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017\u0002\u0018\u0007\u0018"+
		"\u0002\u0019\u0007\u0019\u0002\u001a\u0007\u001a\u0002\u001b\u0007\u001b"+
		"\u0002\u001c\u0007\u001c\u0002\u001d\u0007\u001d\u0002\u001e\u0007\u001e"+
		"\u0002\u001f\u0007\u001f\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000"+
		"\u0003\u0000E\b\u0000\u0001\u0000\u0005\u0000H\b\u0000\n\u0000\f\u0000"+
		"K\t\u0000\u0001\u0000\u0005\u0000N\b\u0000\n\u0000\f\u0000Q\t\u0000\u0001"+
		"\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001\u0005"+
		"\u0001Y\b\u0001\n\u0001\f\u0001\\\t\u0001\u0001\u0002\u0001\u0002\u0001"+
		"\u0002\u0001\u0002\u0001\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0005"+
		"\u0003f\b\u0003\n\u0003\f\u0003i\t\u0003\u0001\u0004\u0001\u0004\u0001"+
		"\u0004\u0001\u0004\u0001\u0004\u0003\u0004p\b\u0004\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0005\u0006}\b\u0006\n\u0006"+
		"\f\u0006\u0080\t\u0006\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007"+
		"\u0001\u0007\u0001\u0007\u0005\u0007\u0088\b\u0007\n\u0007\f\u0007\u008b"+
		"\t\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\b\u0001"+
		"\b\u0001\b\u0001\b\u0001\t\u0001\t\u0001\t\u0001\t\u0001\n\u0001\n\u0001"+
		"\n\u0005\n\u009c\b\n\n\n\f\n\u009f\t\n\u0001\u000b\u0001\u000b\u0001\u000b"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0003\u000b\u00a8\b\u000b"+
		"\u0001\f\u0001\f\u0001\f\u0001\f\u0001\r\u0001\r\u0003\r\u00b0\b\r\u0001"+
		"\r\u0001\r\u0001\r\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0003\u000e\u00ba\b\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0003"+
		"\u000e\u00bf\b\u000e\u0003\u000e\u00c1\b\u000e\u0001\u000f\u0001\u000f"+
		"\u0001\u000f\u0003\u000f\u00c6\b\u000f\u0001\u000f\u0003\u000f\u00c9\b"+
		"\u000f\u0001\u000f\u0001\u000f\u0001\u000f\u0003\u000f\u00ce\b\u000f\u0001"+
		"\u000f\u0003\u000f\u00d1\b\u000f\u0003\u000f\u00d3\b\u000f\u0001\u0010"+
		"\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0005\u0010\u00da\b\u0010"+
		"\n\u0010\f\u0010\u00dd\t\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001"+
		"\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0005\u0010\u00e6\b\u0010\n"+
		"\u0010\f\u0010\u00e9\t\u0010\u0001\u0010\u0001\u0010\u0003\u0010\u00ed"+
		"\b\u0010\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001"+
		"\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0003\u0011\u00f9"+
		"\b\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0003"+
		"\u0011\u0100\b\u0011\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001"+
		"\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001"+
		"\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0003\u0012\u0111"+
		"\b\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001"+
		"\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001"+
		"\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001"+
		"\u0012\u0005\u0012\u0125\b\u0012\n\u0012\f\u0012\u0128\t\u0012\u0001\u0013"+
		"\u0001\u0013\u0001\u0014\u0001\u0014\u0001\u0015\u0001\u0015\u0001\u0016"+
		"\u0001\u0016\u0001\u0017\u0001\u0017\u0001\u0017\u0001\u0017\u0001\u0017"+
		"\u0001\u0017\u0001\u0017\u0001\u0017\u0003\u0017\u013a\b\u0017\u0001\u0018"+
		"\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0018\u0003\u0018"+
		"\u0142\b\u0018\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0019\u0001\u0019"+
		"\u0001\u0019\u0001\u0019\u0001\u0019\u0001\u0019\u0001\u0019\u0001\u0019"+
		"\u0005\u0019\u014f\b\u0019\n\u0019\f\u0019\u0152\t\u0019\u0001\u001a\u0003"+
		"\u001a\u0155\b\u001a\u0001\u001a\u0001\u001a\u0001\u001a\u0001\u001b\u0001"+
		"\u001b\u0001\u001b\u0003\u001b\u015d\b\u001b\u0001\u001b\u0001\u001b\u0001"+
		"\u001c\u0001\u001c\u0001\u001c\u0005\u001c\u0164\b\u001c\n\u001c\f\u001c"+
		"\u0167\t\u001c\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001d"+
		"\u0001\u001d\u0001\u001d\u0001\u001d\u0003\u001d\u0171\b\u001d\u0001\u001e"+
		"\u0001\u001e\u0001\u001e\u0001\u001e\u0001\u001e\u0001\u001e\u0003\u001e"+
		"\u0179\b\u001e\u0001\u001f\u0003\u001f\u017c\b\u001f\u0001\u001f\u0001"+
		"\u001f\u0001\u001f\u0001\u001f\u0000\u0001$ \u0000\u0002\u0004\u0006\b"+
		"\n\f\u000e\u0010\u0012\u0014\u0016\u0018\u001a\u001c\u001e \"$&(*,.02"+
		"468:<>\u0000\u0005\u0002\u0000\u001f\u001f99\u0002\u0000BBFF\u0003\u0000"+
		"\n\u000b\u001d\u001d**\u0001\u0000\b\t\u0001\u0000\u0002\u0007\u0198\u0000"+
		"@\u0001\u0000\u0000\u0000\u0002V\u0001\u0000\u0000\u0000\u0004]\u0001"+
		"\u0000\u0000\u0000\u0006b\u0001\u0000\u0000\u0000\bo\u0001\u0000\u0000"+
		"\u0000\nq\u0001\u0000\u0000\u0000\fx\u0001\u0000\u0000\u0000\u000e\u0083"+
		"\u0001\u0000\u0000\u0000\u0010\u0090\u0001\u0000\u0000\u0000\u0012\u0094"+
		"\u0001\u0000\u0000\u0000\u0014\u009d\u0001\u0000\u0000\u0000\u0016\u00a7"+
		"\u0001\u0000\u0000\u0000\u0018\u00a9\u0001\u0000\u0000\u0000\u001a\u00af"+
		"\u0001\u0000\u0000\u0000\u001c\u00b4\u0001\u0000\u0000\u0000\u001e\u00d2"+
		"\u0001\u0000\u0000\u0000 \u00ec\u0001\u0000\u0000\u0000\"\u00ee\u0001"+
		"\u0000\u0000\u0000$\u0110\u0001\u0000\u0000\u0000&\u0129\u0001\u0000\u0000"+
		"\u0000(\u012b\u0001\u0000\u0000\u0000*\u012d\u0001\u0000\u0000\u0000,"+
		"\u012f\u0001\u0000\u0000\u0000.\u0139\u0001\u0000\u0000\u00000\u013b\u0001"+
		"\u0000\u0000\u00002\u0146\u0001\u0000\u0000\u00004\u0154\u0001\u0000\u0000"+
		"\u00006\u0159\u0001\u0000\u0000\u00008\u0160\u0001\u0000\u0000\u0000:"+
		"\u0170\u0001\u0000\u0000\u0000<\u0172\u0001\u0000\u0000\u0000>\u017b\u0001"+
		"\u0000\u0000\u0000@A\u00051\u0000\u0000AB\u0005F\u0000\u0000BD\u0005\u0012"+
		"\u0000\u0000CE\u0003\u0002\u0001\u0000DC\u0001\u0000\u0000\u0000DE\u0001"+
		"\u0000\u0000\u0000EI\u0001\u0000\u0000\u0000FH\u0003.\u0017\u0000GF\u0001"+
		"\u0000\u0000\u0000HK\u0001\u0000\u0000\u0000IG\u0001\u0000\u0000\u0000"+
		"IJ\u0001\u0000\u0000\u0000JO\u0001\u0000\u0000\u0000KI\u0001\u0000\u0000"+
		"\u0000LN\u0003:\u001d\u0000ML\u0001\u0000\u0000\u0000NQ\u0001\u0000\u0000"+
		"\u0000OM\u0001\u0000\u0000\u0000OP\u0001\u0000\u0000\u0000PR\u0001\u0000"+
		"\u0000\u0000QO\u0001\u0000\u0000\u0000RS\u0003\u0012\t\u0000ST\u0005\u0013"+
		"\u0000\u0000TU\u0005\u0000\u0000\u0001U\u0001\u0001\u0000\u0000\u0000"+
		"VZ\u0005<\u0000\u0000WY\u0003\u0004\u0002\u0000XW\u0001\u0000\u0000\u0000"+
		"Y\\\u0001\u0000\u0000\u0000ZX\u0001\u0000\u0000\u0000Z[\u0001\u0000\u0000"+
		"\u0000[\u0003\u0001\u0000\u0000\u0000\\Z\u0001\u0000\u0000\u0000]^\u0003"+
		"\u0006\u0003\u0000^_\u0005\u0011\u0000\u0000_`\u0003\b\u0004\u0000`a\u0005"+
		"\u0012\u0000\u0000a\u0005\u0001\u0000\u0000\u0000bg\u0005F\u0000\u0000"+
		"cd\u0005\u0010\u0000\u0000df\u0005F\u0000\u0000ec\u0001\u0000\u0000\u0000"+
		"fi\u0001\u0000\u0000\u0000ge\u0001\u0000\u0000\u0000gh\u0001\u0000\u0000"+
		"\u0000h\u0007\u0001\u0000\u0000\u0000ig\u0001\u0000\u0000\u0000jp\u0005"+
		"\u0019\u0000\u0000kp\u0005(\u0000\u0000lp\u00053\u0000\u0000mp\u00057"+
		"\u0000\u0000np\u0003\n\u0005\u0000oj\u0001\u0000\u0000\u0000ok\u0001\u0000"+
		"\u0000\u0000ol\u0001\u0000\u0000\u0000om\u0001\u0000\u0000\u0000on\u0001"+
		"\u0000\u0000\u0000p\t\u0001\u0000\u0000\u0000qr\u0005\u0017\u0000\u0000"+
		"rs\u0005\u000e\u0000\u0000st\u0003\u0010\b\u0000tu\u0005\u000f\u0000\u0000"+
		"uv\u0005-\u0000\u0000vw\u0003\b\u0004\u0000w\u000b\u0001\u0000\u0000\u0000"+
		"xy\u0005F\u0000\u0000yz\u0005\u000e\u0000\u0000z~\u0003$\u0012\u0000{"+
		"}\u0003$\u0012\u0000|{\u0001\u0000\u0000\u0000}\u0080\u0001\u0000\u0000"+
		"\u0000~|\u0001\u0000\u0000\u0000~\u007f\u0001\u0000\u0000\u0000\u007f"+
		"\u0081\u0001\u0000\u0000\u0000\u0080~\u0001\u0000\u0000\u0000\u0081\u0082"+
		"\u0005\u000f\u0000\u0000\u0082\r\u0001\u0000\u0000\u0000\u0083\u0084\u0005"+
		"F\u0000\u0000\u0084\u0085\u0005\u000e\u0000\u0000\u0085\u0089\u0003$\u0012"+
		"\u0000\u0086\u0088\u0003$\u0012\u0000\u0087\u0086\u0001\u0000\u0000\u0000"+
		"\u0088\u008b\u0001\u0000\u0000\u0000\u0089\u0087\u0001\u0000\u0000\u0000"+
		"\u0089\u008a\u0001\u0000\u0000\u0000\u008a\u008c\u0001\u0000\u0000\u0000"+
		"\u008b\u0089\u0001\u0000\u0000\u0000\u008c\u008d\u0005\u000f\u0000\u0000"+
		"\u008d\u008e\u0005\u0001\u0000\u0000\u008e\u008f\u0003$\u0012\u0000\u008f"+
		"\u000f\u0001\u0000\u0000\u0000\u0090\u0091\u0005B\u0000\u0000\u0091\u0092"+
		"\u0005\u0014\u0000\u0000\u0092\u0093\u0005B\u0000\u0000\u0093\u0011\u0001"+
		"\u0000\u0000\u0000\u0094\u0095\u0005\u0018\u0000\u0000\u0095\u0096\u0003"+
		"\u0014\n\u0000\u0096\u0097\u0005!\u0000\u0000\u0097\u0013\u0001\u0000"+
		"\u0000\u0000\u0098\u0099\u0003\u0016\u000b\u0000\u0099\u009a\u0005\u0012"+
		"\u0000\u0000\u009a\u009c\u0001\u0000\u0000\u0000\u009b\u0098\u0001\u0000"+
		"\u0000\u0000\u009c\u009f\u0001\u0000\u0000\u0000\u009d\u009b\u0001\u0000"+
		"\u0000\u0000\u009d\u009e\u0001\u0000\u0000\u0000\u009e\u0015\u0001\u0000"+
		"\u0000\u0000\u009f\u009d\u0001\u0000\u0000\u0000\u00a0\u00a8\u0003\u001a"+
		"\r\u0000\u00a1\u00a8\u0003\u001c\u000e\u0000\u00a2\u00a8\u0003\u001e\u000f"+
		"\u0000\u00a3\u00a8\u0003 \u0010\u0000\u00a4\u00a8\u0003\u0018\f\u0000"+
		"\u00a5\u00a8\u0003\"\u0011\u0000\u00a6\u00a8\u00036\u001b\u0000\u00a7"+
		"\u00a0\u0001\u0000\u0000\u0000\u00a7\u00a1\u0001\u0000\u0000\u0000\u00a7"+
		"\u00a2\u0001\u0000\u0000\u0000\u00a7\u00a3\u0001\u0000\u0000\u0000\u00a7"+
		"\u00a4\u0001\u0000\u0000\u0000\u00a7\u00a5\u0001\u0000\u0000\u0000\u00a7"+
		"\u00a6\u0001\u0000\u0000\u0000\u00a8\u0017\u0001\u0000\u0000\u0000\u00a9"+
		"\u00aa\u0005\u0018\u0000\u0000\u00aa\u00ab\u0003\u0014\n\u0000\u00ab\u00ac"+
		"\u0005!\u0000\u0000\u00ac\u0019\u0001\u0000\u0000\u0000\u00ad\u00b0\u0005"+
		"F\u0000\u0000\u00ae\u00b0\u0003\f\u0006\u0000\u00af\u00ad\u0001\u0000"+
		"\u0000\u0000\u00af\u00ae\u0001\u0000\u0000\u0000\u00b0\u00b1\u0001\u0000"+
		"\u0000\u0000\u00b1\u00b2\u0005\u0001\u0000\u0000\u00b2\u00b3\u0003$\u0012"+
		"\u0000\u00b3\u001b\u0001\u0000\u0000\u0000\u00b4\u00b5\u0005&\u0000\u0000"+
		"\u00b5\u00b6\u0003$\u0012\u0000\u00b6\u00b9\u00058\u0000\u0000\u00b7\u00ba"+
		"\u0003\u0016\u000b\u0000\u00b8\u00ba\u0003\u0018\f\u0000\u00b9\u00b7\u0001"+
		"\u0000\u0000\u0000\u00b9\u00b8\u0001\u0000\u0000\u0000\u00ba\u00c0\u0001"+
		"\u0000\u0000\u0000\u00bb\u00be\u0005 \u0000\u0000\u00bc\u00bf\u0003\u0016"+
		"\u000b\u0000\u00bd\u00bf\u0003\u0018\f\u0000\u00be\u00bc\u0001\u0000\u0000"+
		"\u0000\u00be\u00bd\u0001\u0000\u0000\u0000\u00bf\u00c1\u0001\u0000\u0000"+
		"\u0000\u00c0\u00bb\u0001\u0000\u0000\u0000\u00c0\u00c1\u0001\u0000\u0000"+
		"\u0000\u00c1\u001d\u0001\u0000\u0000\u0000\u00c2\u00c8\u0005@\u0000\u0000"+
		"\u00c3\u00c5\u0005\f\u0000\u0000\u00c4\u00c6\u0005F\u0000\u0000\u00c5"+
		"\u00c4\u0001\u0000\u0000\u0000\u00c5\u00c6\u0001\u0000\u0000\u0000\u00c6"+
		"\u00c7\u0001\u0000\u0000\u0000\u00c7\u00c9\u0005\r\u0000\u0000\u00c8\u00c3"+
		"\u0001\u0000\u0000\u0000\u00c8\u00c9\u0001\u0000\u0000\u0000\u00c9\u00d3"+
		"\u0001\u0000\u0000\u0000\u00ca\u00d0\u00052\u0000\u0000\u00cb\u00cd\u0005"+
		"\f\u0000\u0000\u00cc\u00ce\u0005F\u0000\u0000\u00cd\u00cc\u0001\u0000"+
		"\u0000\u0000\u00cd\u00ce\u0001\u0000\u0000\u0000\u00ce\u00cf\u0001\u0000"+
		"\u0000\u0000\u00cf\u00d1\u0005\r\u0000\u0000\u00d0\u00cb\u0001\u0000\u0000"+
		"\u0000\u00d0\u00d1\u0001\u0000\u0000\u0000\u00d1\u00d3\u0001\u0000\u0000"+
		"\u0000\u00d2\u00c2\u0001\u0000\u0000\u0000\u00d2\u00ca\u0001\u0000\u0000"+
		"\u0000\u00d3\u001f\u0001\u0000\u0000\u0000\u00d4\u00d5\u0005A\u0000\u0000"+
		"\u00d5\u00d6\u0005\f\u0000\u0000\u00d6\u00db\u0003$\u0012\u0000\u00d7"+
		"\u00d8\u0005\u0010\u0000\u0000\u00d8\u00da\u0003$\u0012\u0000\u00d9\u00d7"+
		"\u0001\u0000\u0000\u0000\u00da\u00dd\u0001\u0000\u0000\u0000\u00db\u00d9"+
		"\u0001\u0000\u0000\u0000\u00db\u00dc\u0001\u0000\u0000\u0000\u00dc\u00de"+
		"\u0001\u0000\u0000\u0000\u00dd\u00db\u0001\u0000\u0000\u0000\u00de\u00df"+
		"\u0005\r\u0000\u0000\u00df\u00ed\u0001\u0000\u0000\u0000\u00e0\u00e1\u0005"+
		"?\u0000\u0000\u00e1\u00e2\u0005\f\u0000\u0000\u00e2\u00e7\u0003$\u0012"+
		"\u0000\u00e3\u00e4\u0005\u0010\u0000\u0000\u00e4\u00e6\u0003$\u0012\u0000"+
		"\u00e5\u00e3\u0001\u0000\u0000\u0000\u00e6\u00e9\u0001\u0000\u0000\u0000"+
		"\u00e7\u00e5\u0001\u0000\u0000\u0000\u00e7\u00e8\u0001\u0000\u0000\u0000"+
		"\u00e8\u00ea\u0001\u0000\u0000\u0000\u00e9\u00e7\u0001\u0000\u0000\u0000"+
		"\u00ea\u00eb\u0005\r\u0000\u0000\u00eb\u00ed\u0001\u0000\u0000\u0000\u00ec"+
		"\u00d4\u0001\u0000\u0000\u0000\u00ec\u00e0\u0001\u0000\u0000\u0000\u00ed"+
		"!\u0001\u0000\u0000\u0000\u00ee\u00ef\u0005#\u0000\u0000\u00ef\u00f0\u0005"+
		"F\u0000\u0000\u00f0\u00f1\u0005\u0001\u0000\u0000\u00f1\u00f2\u0003&\u0013"+
		"\u0000\u00f2\u00f3\u0007\u0000\u0000\u0000\u00f3\u00f4\u0003&\u0013\u0000"+
		"\u00f4\u00ff\u0005\u001e\u0000\u0000\u00f5\u00f6\u0005\u0018\u0000\u0000"+
		"\u00f6\u00f8\u0003\u0016\u000b\u0000\u00f7\u00f9\u0005\u0012\u0000\u0000"+
		"\u00f8\u00f7\u0001\u0000\u0000\u0000\u00f8\u00f9\u0001\u0000\u0000\u0000"+
		"\u00f9\u00fa\u0001\u0000\u0000\u0000\u00fa\u00fb\u0005!\u0000\u0000\u00fb"+
		"\u00fc\u0005\u0012\u0000\u0000\u00fc\u0100\u0001\u0000\u0000\u0000\u00fd"+
		"\u0100\u0003\u0016\u000b\u0000\u00fe\u0100\u0003\u0018\f\u0000\u00ff\u00f5"+
		"\u0001\u0000\u0000\u0000\u00ff\u00fd\u0001\u0000\u0000\u0000\u00ff\u00fe"+
		"\u0001\u0000\u0000\u0000\u0100#\u0001\u0000\u0000\u0000\u0101\u0102\u0006"+
		"\u0012\uffff\uffff\u0000\u0102\u0103\u0005,\u0000\u0000\u0103\u0111\u0003"+
		"$\u0012\n\u0104\u0105\u0005\f\u0000\u0000\u0105\u0106\u0003$\u0012\u0000"+
		"\u0106\u0107\u0005\r\u0000\u0000\u0107\u0111\u0001\u0000\u0000\u0000\u0108"+
		"\u0111\u0005D\u0000\u0000\u0109\u0111\u0005B\u0000\u0000\u010a\u0111\u0005"+
		"C\u0000\u0000\u010b\u0111\u0005E\u0000\u0000\u010c\u0111\u0005F\u0000"+
		"\u0000\u010d\u0111\u00036\u001b\u0000\u010e\u0111\u0003\f\u0006\u0000"+
		"\u010f\u0111\u0003\u000e\u0007\u0000\u0110\u0101\u0001\u0000\u0000\u0000"+
		"\u0110\u0104\u0001\u0000\u0000\u0000\u0110\u0108\u0001\u0000\u0000\u0000"+
		"\u0110\u0109\u0001\u0000\u0000\u0000\u0110\u010a\u0001\u0000\u0000\u0000"+
		"\u0110\u010b\u0001\u0000\u0000\u0000\u0110\u010c\u0001\u0000\u0000\u0000"+
		"\u0110\u010d\u0001\u0000\u0000\u0000\u0110\u010e\u0001\u0000\u0000\u0000"+
		"\u0110\u010f\u0001\u0000\u0000\u0000\u0111\u0126\u0001\u0000\u0000\u0000"+
		"\u0112\u0113\n\u000f\u0000\u0000\u0113\u0114\u0005\u0016\u0000\u0000\u0114"+
		"\u0125\u0003$\u0012\u0010\u0115\u0116\n\u000e\u0000\u0000\u0116\u0117"+
		"\u0005.\u0000\u0000\u0117\u0125\u0003$\u0012\u000f\u0118\u0119\n\r\u0000"+
		"\u0000\u0119\u011a\u0003,\u0016\u0000\u011a\u011b\u0003$\u0012\u000e\u011b"+
		"\u0125\u0001\u0000\u0000\u0000\u011c\u011d\n\f\u0000\u0000\u011d\u011e"+
		"\u0003*\u0015\u0000\u011e\u011f\u0003$\u0012\r\u011f\u0125\u0001\u0000"+
		"\u0000\u0000\u0120\u0121\n\u000b\u0000\u0000\u0121\u0122\u0003(\u0014"+
		"\u0000\u0122\u0123\u0003$\u0012\f\u0123\u0125\u0001\u0000\u0000\u0000"+
		"\u0124\u0112\u0001\u0000\u0000\u0000\u0124\u0115\u0001\u0000\u0000\u0000"+
		"\u0124\u0118\u0001\u0000\u0000\u0000\u0124\u011c\u0001\u0000\u0000\u0000"+
		"\u0124\u0120\u0001\u0000\u0000\u0000\u0125\u0128\u0001\u0000\u0000\u0000"+
		"\u0126\u0124\u0001\u0000\u0000\u0000\u0126\u0127\u0001\u0000\u0000\u0000"+
		"\u0127%\u0001\u0000\u0000\u0000\u0128\u0126\u0001\u0000\u0000\u0000\u0129"+
		"\u012a\u0007\u0001\u0000\u0000\u012a\'\u0001\u0000\u0000\u0000\u012b\u012c"+
		"\u0007\u0002\u0000\u0000\u012c)\u0001\u0000\u0000\u0000\u012d\u012e\u0007"+
		"\u0003\u0000\u0000\u012e+\u0001\u0000\u0000\u0000\u012f\u0130\u0007\u0004"+
		"\u0000\u0000\u0130-\u0001\u0000\u0000\u0000\u0131\u0132\u00030\u0018\u0000"+
		"\u0132\u0133\u0005\u0012\u0000\u0000\u0133\u0134\u00034\u001a\u0000\u0134"+
		"\u013a\u0001\u0000\u0000\u0000\u0135\u0136\u0005$\u0000\u0000\u0136\u0137"+
		"\u0005F\u0000\u0000\u0137\u0138\u0005\u0011\u0000\u0000\u0138\u013a\u0003"+
		"4\u001a\u0000\u0139\u0131\u0001\u0000\u0000\u0000\u0139\u0135\u0001\u0000"+
		"\u0000\u0000\u013a/\u0001\u0000\u0000\u0000\u013b\u013c\u0005$\u0000\u0000"+
		"\u013c\u0141\u0005F\u0000\u0000\u013d\u013e\u0005\f\u0000\u0000\u013e"+
		"\u013f\u00032\u0019\u0000\u013f\u0140\u0005\r\u0000\u0000\u0140\u0142"+
		"\u0001\u0000\u0000\u0000\u0141\u013d\u0001\u0000\u0000\u0000\u0141\u0142"+
		"\u0001\u0000\u0000\u0000\u0142\u0143\u0001\u0000\u0000\u0000\u0143\u0144"+
		"\u0005\u0011\u0000\u0000\u0144\u0145\u0003\b\u0004\u0000\u01451\u0001"+
		"\u0000\u0000\u0000\u0146\u0147\u0003\u0006\u0003\u0000\u0147\u0148\u0005"+
		"\u0011\u0000\u0000\u0148\u0150\u0003\b\u0004\u0000\u0149\u014a\u0005\u0012"+
		"\u0000\u0000\u014a\u014b\u0003\u0006\u0003\u0000\u014b\u014c\u0005\u0011"+
		"\u0000\u0000\u014c\u014d\u0003\b\u0004\u0000\u014d\u014f\u0001\u0000\u0000"+
		"\u0000\u014e\u0149\u0001\u0000\u0000\u0000\u014f\u0152\u0001\u0000\u0000"+
		"\u0000\u0150\u014e\u0001\u0000\u0000\u0000\u0150\u0151\u0001\u0000\u0000"+
		"\u0000\u01513\u0001\u0000\u0000\u0000\u0152\u0150\u0001\u0000\u0000\u0000"+
		"\u0153\u0155\u0003\u0002\u0001\u0000\u0154\u0153\u0001\u0000\u0000\u0000"+
		"\u0154\u0155\u0001\u0000\u0000\u0000\u0155\u0156\u0001\u0000\u0000\u0000"+
		"\u0156\u0157\u0003\u0012\t\u0000\u0157\u0158\u0005\u0012\u0000\u0000\u0158"+
		"5\u0001\u0000\u0000\u0000\u0159\u015a\u0005F\u0000\u0000\u015a\u015c\u0005"+
		"\f\u0000\u0000\u015b\u015d\u00038\u001c\u0000\u015c\u015b\u0001\u0000"+
		"\u0000\u0000\u015c\u015d\u0001\u0000\u0000\u0000\u015d\u015e\u0001\u0000"+
		"\u0000\u0000\u015e\u015f\u0005\r\u0000\u0000\u015f7\u0001\u0000\u0000"+
		"\u0000\u0160\u0165\u0003$\u0012\u0000\u0161\u0162\u0005\u0010\u0000\u0000"+
		"\u0162\u0164\u0003$\u0012\u0000\u0163\u0161\u0001\u0000\u0000\u0000\u0164"+
		"\u0167\u0001\u0000\u0000\u0000\u0165\u0163\u0001\u0000\u0000\u0000\u0165"+
		"\u0166\u0001\u0000\u0000\u0000\u01669\u0001\u0000\u0000\u0000\u0167\u0165"+
		"\u0001\u0000\u0000\u0000\u0168\u0169\u0003<\u001e\u0000\u0169\u016a\u0005"+
		"\u0012\u0000\u0000\u016a\u016b\u0003>\u001f\u0000\u016b\u0171\u0001\u0000"+
		"\u0000\u0000\u016c\u016d\u00050\u0000\u0000\u016d\u016e\u0005F\u0000\u0000"+
		"\u016e\u016f\u0005\u0011\u0000\u0000\u016f\u0171\u0003>\u001f\u0000\u0170"+
		"\u0168\u0001\u0000\u0000\u0000\u0170\u016c\u0001\u0000\u0000\u0000\u0171"+
		";\u0001\u0000\u0000\u0000\u0172\u0173\u00050\u0000\u0000\u0173\u0178\u0005"+
		"F\u0000\u0000\u0174\u0175\u0005\f\u0000\u0000\u0175\u0176\u00032\u0019"+
		"\u0000\u0176\u0177\u0005\r\u0000\u0000\u0177\u0179\u0001\u0000\u0000\u0000"+
		"\u0178\u0174\u0001\u0000\u0000\u0000\u0178\u0179\u0001\u0000\u0000\u0000"+
		"\u0179=\u0001\u0000\u0000\u0000\u017a\u017c\u0003\u0002\u0001\u0000\u017b"+
		"\u017a\u0001\u0000\u0000\u0000\u017b\u017c\u0001\u0000\u0000\u0000\u017c"+
		"\u017d\u0001\u0000\u0000\u0000\u017d\u017e\u0003\u0012\t\u0000\u017e\u017f"+
		"\u0005\u0012\u0000\u0000\u017f?\u0001\u0000\u0000\u0000$DIOZgo~\u0089"+
		"\u009d\u00a7\u00af\u00b9\u00be\u00c0\u00c5\u00c8\u00cd\u00d0\u00d2\u00db"+
		"\u00e7\u00ec\u00f8\u00ff\u0110\u0124\u0126\u0139\u0141\u0150\u0154\u015c"+
		"\u0165\u0170\u0178\u017b";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}