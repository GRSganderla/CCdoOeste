package semantica;

import compiladorcc.SimpleNode;
import compiladorcc.Token;
import symtable.*;

public class SemanticRun {

	private Symtable simbolos;
	private int foundSemanticError;
	
	public Symtable getSimbolos() {
		return simbolos;
	}

	public void setSimbolos(Symtable simbolos) {
		this.simbolos = simbolos;
	}

	public int getFoundSemanticError() {
		return foundSemanticError;
	}

	public void setFoundSemanticError(int foundSemanticError) {
		this.foundSemanticError = foundSemanticError;
	}

	public SemanticRun(){
		
		simbolos = new Symtable();
		foundSemanticError = 0;
	}
	
	public void programCheck(SimpleNode root) throws SemanticException{
		
		int i;
		
		for(i = 0; i < root.jjtGetNumChildren(); i++) {
			
			func_listCheck((SimpleNode) root.jjtGetChild(i));
		}
		
		if(foundSemanticError != 0)
			throw new SemanticException (foundSemanticError + " Erros Semanticos encontrados");
	}
	
	public void func_listCheck(SimpleNode alvo){
		
		if(alvo == null) return;

		System.out.println("ALO"+ alvo.jjtGetNumChildren());
		if(alvo.jjtGetNumChildren() > 0){
			try {
				func_declCheck((SimpleNode)alvo.jjtGetChild(0));
			} catch (SemanticException e) {
				// TODO Auto-generated catch block
				System.err.println(e.getMessage());
				foundSemanticError++;
			}
		}
		
		if(alvo.jjtGetNumChildren() > 1) {
			func_listCheck((SimpleNode)alvo.jjtGetChild(1));
		}
	}
	
	public void func_declCheck(SimpleNode alvo) throws SemanticException {
		
		if(alvo == null) return;
		int pos = simbolos.getPos();
		String nome_proc = alvo.value1;
		
		if(nome_proc == null) return;
		String retorno = null;
		
		if(alvo.jjtGetChild(0) != null) {
			retorno = func_typeCheck((SimpleNode)alvo.jjtGetChild(0));
			System.out.println(retorno);
		}
		
		if(simbolos.find(nome_proc, "Global") == 0) {
			if(nome_proc.equals("main"))
				simbolos.add(new EntryTable(nome_proc, "keyword", "proc", retorno, "None", "Global"));
			else
				simbolos.add(new EntryTable(nome_proc, "id", "proc", retorno, "None", "Global"));
		}
		else
			throw new SemanticException("Função/Procedimento "+ nome_proc +" ja declarada");
		
		if(alvo.jjtGetChild(1) != null) {
			try {
				param_listCheck((SimpleNode)alvo.jjtGetChild(1));
			}catch(SemanticException e) {
				System.err.println(e.getMessage());
				foundSemanticError++;
			}
		}
		
		if(alvo.jjtGetNumChildren() > 2) {
			if(alvo.jjtGetChild(2) != null) {
				func_bodyCheck((SimpleNode)alvo.jjtGetChild(2), pos);
			}
		}
		
		System.out.println(simbolos.toString());
		
		while(pos+1 < simbolos.getPos())
			simbolos.retira();
		
		System.out.println(simbolos.toString());
	}
	  
	private void func_bodyCheck(SimpleNode body, int pos) {
		
		if(body == null) return;
		
		for(int i = 0; i < body.jjtGetNumChildren(); i++) {
			SimpleNode filho = (SimpleNode)body.jjtGetChild(i);
			try {
				switch(filho.jjtGetId()) {
					case 4:
						var_listCheck(filho);
						break;
					case 8:
						ifCheck(filho);
						break;
					case 10:
						forCheck(filho);
						break;
					case 11:
						whileCheck(filho);
						break;
					case 12:
						atribCheck(filho);
						break;
					case 7:
						returnCheck(filho, pos);
						break;
				}
			}catch(SemanticException e) {
				System.err.println(e.getMessage());
				foundSemanticError++;
			}
		}
	}

	private void returnCheck(SimpleNode filho, int pos) throws SemanticException {
		
		if(filho == null) return;
		
		String tipo = (simbolos.getType(pos) == null)? "Null" : simbolos.getType(pos);
		String ret[] = {"None"};
		
		if(filho.jjtGetNumChildren() > 1) {
			if(filho.jjtGetChild(0) != null) {
				ret = expressaoCheck((SimpleNode)filho.jjtGetChild(0));
			}
		}
		
		if(!tipo.equals(ret[0])) {
			throw new SemanticException("Este metodo deve retornar um Tipo "+tipo);
		}
	}

	private String[] expressaoCheck(SimpleNode jjtGetChild) throws SemanticException {
		
		if(jjtGetChild == null) return null;
		
		String num1[] = null, num2[] = null;
		
		if(jjtGetChild.jjtGetChild(0) != null) {
			num1 = numexpCheck((SimpleNode)jjtGetChild.jjtGetChild(0));
		}
		
		if(jjtGetChild.jjtGetChild(1)!= null) {
			num2 = numexpCheck((SimpleNode)jjtGetChild.jjtGetChild(1));
		}
		
		Token op = jjtGetChild.k;

		if(num1[1].equals(num2[1])) {
			switch(op.kind) {
			case 18:
				break;
			case 17:
				break;
			case 20:
				break;
			case 19:
				break;
			case 21:
				break;
			case 22:
				break;
			case 9:
				break;
			case 10:
				break;
			}
		}
		else {
			throw new SemanticException("Os tipos de dados são incompativeis");
		}
		
		return new String[] {"bla"};
	}

	private String[] numexpCheck(SimpleNode exp) throws SemanticException {
		
		if(exp == null) return null;
		String op = (exp.value1 == null)? "None" : exp.value1;
		
		Token num1 = null;
		if(exp.jjtGetChild(0)!= null)
			num1 = termCheck((SimpleNode)exp.jjtGetChild(0));
		
		Token num2 = null;
		if(exp.jjtGetNumChildren() > 1) {
			if(exp.jjtGetChild(1)!= null)
				num2 = termCheck((SimpleNode)exp.jjtGetChild(1));
		}
		
		if(op.equals("+") && num2 != null) {
			switch(num1.kind) {
			case 1:
				break;
			}
			
			return new String []{"bla"};
		}
		else if(op.equals("-") && num2 != null) {
			return new String [] {"blu"};
		}
		else {
			return new String [] {op};
		}
	}

	private Token termCheck(SimpleNode term) throws SemanticException {
		
		if(term == null) return null;
		
		String op = (term.value1 == null)? "None" : term.value1;
		
		Token[] num1 = null;
		if(term.jjtGetChild(0)!= null)
			num1 = unaryexpCheck((SimpleNode)term.jjtGetChild(0));
		
		Token[] num2 = null;
		if(term.jjtGetNumChildren() > 1) {
			if(term.jjtGetChild(1)!= null)
				num2 = unaryexpCheck((SimpleNode)term.jjtGetChild(1));
		}
		
		if(op.equals("*") && num2 != null) {
			switch(num1[0].kind) {
			case 1:
				break;
			}
			
			return num1[0];
		}
		else if(op.equals("/") && num2 != null) {
			return num1[0];
		}
		else {
			return num1[0];
		}
	}

	private Token[] unaryexpCheck(SimpleNode unary) throws SemanticException {
		
		String sinal = unary.value1;
			
		if(!sinal.equals("None")) {
			Token a = factorCheck((SimpleNode)unary.jjtGetChild(0));
			Token sinala = unary.k;
			
			return new Token[] {a, sinala};
		}
		else {
			
			return new Token[] {factorCheck((SimpleNode)unary.jjtGetChild(0)), null};
		}
	}

	private Token factorCheck(SimpleNode jjtGetChild) throws SemanticException {
		
		String not = jjtGetChild.value1;
		Token result = new Token(), var = jjtGetChild.k;
		
		if(var.kind == 46) return null;
		else if(var.kind == 49) {
			if(simbolos.find(var.image) == 0)
				throw new SemanticException("Variavel "+ var.image +" nao declarada!");
			else {
				result.kind = var.kind;
				result.image = simbolos.getValor(var.image);
				if(var.image.equals("None")) return null;
				else return result;
			}
		}
		else if(var.kind == 35) {
			
			String[] exp = expressaoCheck((SimpleNode)jjtGetChild.jjtGetChild(0));
			result.image = exp[0];
			result.kind = Integer.parseInt(exp[1]);
			
			if(not.equals("None")) {
				return result;
			}
			else {
				if(result.kind == 44) {
					int img = Integer.parseInt(result.image);
					img = (img == 0)? 1: 0;
					result.image = Integer.toString(img);
					return result;
				}
			}
		}
		else {
		
			return var;
		}
		return var;
	}

	private void atribCheck(SimpleNode filho) throws SemanticException {
		
		if(filho == null) return;
		
		String id = filho.value1;
		
		if(simbolos.find(id) == 0) {
			throw new SemanticException("Variavel "+ id +" nao declarada!");
		}
		else
		{
			String[] valor = expressaoCheck((SimpleNode)filho.jjtGetChild(0));
			
			switch (filho.k.kind) {
				case 1:
					break;
			}
		}
	}

	private void whileCheck(SimpleNode filho) {
		// TODO Auto-generated method stub
		
	}

	private void forCheck(SimpleNode filho) {
		// TODO Auto-generated method stub
		
	}

	private void ifCheck(SimpleNode filho) {
		// TODO Auto-generated method stub
		
	}

	private void var_listCheck(SimpleNode filho) throws SemanticException {
		
		if(filho == null) return;
		
		String tipo = filho.value1;
		String nome = filho.value2;
		
		if(simbolos.find(nome, "Local") == 0) {
			simbolos.add(new EntryTable(nome, "id", "var", tipo, "0", "Local"));
		}
		else 
			throw new SemanticException("Variável "+ nome +" já declarada");
	}

	public String func_typeCheck(SimpleNode nod) {
		
		String tipo = nod.value1;
		
		return tipo;
	}
	
	public void param_listCheck(SimpleNode param) throws SemanticException{
		
		if(param.jjtGetNumChildren() == 0) return;
		
		String tipo1 = null, nome1, tipo2 = null, nome2 = null;
		if(param.jjtGetChild(0) != null)
			tipo1 = func_typeCheck((SimpleNode)param.jjtGetChild(0));
		if(param.jjtGetChild(1) != null)
			tipo2 = func_typeCheck((SimpleNode)param.jjtGetChild(1));
		
		nome1 = param.value1;
		if(param.value2 != null) nome2 = param.value2;
		
		simbolos.add(new EntryTable(nome1, "id", "par", tipo1, "0", "Local"));
		if(nome2 != null) simbolos.add(new EntryTable(nome2, "id", "par", tipo2, "0", "Local"));
	}
}