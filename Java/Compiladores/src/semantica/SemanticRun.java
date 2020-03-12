package semantica;

import javacc.SimpleNode;
import javacc.Token;
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

		if(alvo.jjtGetNumChildren() > 0){
			try {
				func_declCheck((SimpleNode)alvo.jjtGetChild(0));
			} catch (SemanticException e) {

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
			param_listCheck((SimpleNode)alvo.jjtGetChild(1));
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
						ifCheck(filho, pos);
						break;
					case 10:
						forCheck(filho, pos);
						break;
					case 11:
						whileCheck(filho, pos);
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
		
		if(filho.jjtGetNumChildren() > 0) {
			if(filho.jjtGetChild(0) != null) {
				try {
					ret = expressaoCheck((SimpleNode)filho.jjtGetChild(0));
				}catch(SemanticException e) {
					System.err.println(e.getMessage());
					foundSemanticError++;
				}
			}
		}

		if(!tipo.equals(ret[1])) {
			throw new SemanticException("Este metodo deve retornar um tipo "+tipo);
		}
	}

	private String[] expressaoCheck(SimpleNode jjtGetChild) throws SemanticException {
		
		if(jjtGetChild == null) return null;
		
		String num1[] = null, num2[] = null;
		
		if(jjtGetChild.jjtGetChild(0) != null) {
			try {
				num1 = numexpCheck((SimpleNode)jjtGetChild.jjtGetChild(0));
			}catch(SemanticException e) {
				System.err.println(e.getMessage());
				foundSemanticError++;
			}
		}
		
		if(jjtGetChild.jjtGetNumChildren() > 1) {
			if(jjtGetChild.jjtGetChild(1)!= null) {
				try {
					num2 = numexpCheck((SimpleNode)jjtGetChild.jjtGetChild(1));
				}catch(SemanticException e) {
					System.err.println(e.getMessage());
					foundSemanticError++;
				}
			}
		}
		
		Token op = jjtGetChild.k;
		String tipo = null;
		String res = new String();
		
		if(num1 != null) {
			if(num1[1].equals("44")) tipo = "int";
			else if(num1[1].equals("45")) tipo = "char";
			else {
				tipo = "Null";
			}
			if(num2 != null) {
				if(num1[1].equals(num2[1]) && !tipo.equals("Null")) {
					
					int num1_v = Integer.parseInt(num1[0]);
					int num2_v = Integer.parseInt(num2[0]);
					
					switch(op.kind) {
					case 18:
						if(num1_v < num2_v) res = "1";
						else res = "0";
						break;
					case 17:
						if(num1_v > num2_v) res = "1";
						else res = "0";
						break;
					case 20:
						if(num1_v <= num2_v) res = "1";
						else res = "0";
						break;
					case 19:
						if(num1_v >= num2_v) res = "1";
						else res = "0";
						break;
					case 21:
						if(num1_v == num2_v) res = "1";
						else res = "0";
						break;
					case 22:
						if(num1_v != num2_v) res = "1";
						else res = "0";
						break;
					case 9:
						if(num1_v > 0  && num2_v > 0) res = "1";
						else res = "0";
						break;
					case 10:
						if(num1_v > 0 || num2_v > 0) res = "1";
						else res = "0";
						break;
					}
				}
				else {
					throw new SemanticException("Os tipos de dados são incompativeis");
				}
			}
			else res = num1[0];
		}
		return new String[] {res, tipo};
	}

	private String[] numexpCheck(SimpleNode exp) throws SemanticException {
		
		if(exp == null) return null;
		String op = (exp.value1 == null)? "None" : exp.value1;
		
		Token num1 = null;
		if(exp.jjtGetChild(0) != null) {
			try {
				num1 = termCheck((SimpleNode)exp.jjtGetChild(0));
			}catch(SemanticException e) {
				System.err.println(e.getMessage());
				foundSemanticError++;
			}
		}
		
		Token num2 = null;
		if(exp.jjtGetNumChildren() > 1) {
			if(exp.jjtGetChild(1)!= null) {
				try {
					num2 = termCheck((SimpleNode)exp.jjtGetChild(1));
				}catch(SemanticException e) {
					System.err.println(e.getMessage());
					foundSemanticError++;
				}
			}
		}
		
		if(num2 != null) {
			if(num1.kind != num2.kind)
				throw new SemanticException("Os tipos de dados são incompativeis");
		}
		
		String resultado;
		
		if(op.equals("+") && num2 != null) {
			
			if(num1.kind != 44)
				throw new SemanticException("Soma nao podem ser feita por tipos diferentes de int");
			
			int num1_valor = Integer.parseInt(num1.image);
			int num2_valor = Integer.parseInt(num2.image);
			
			resultado = Integer.toString(num1_valor + num2_valor);
			
			return new String []{resultado, "44"};
		}
		else if(op.equals("-") && num2 != null) {
			
			if(num1.kind != 44)
				throw new SemanticException("Subtracao nao podem ser feita por tipos diferentes de int");
			
			int num1_valor = Integer.parseInt(num1.image);
			int num2_valor = Integer.parseInt(num2.image);
			
			resultado = Integer.toString(num1_valor - num2_valor);
			
			return new String [] {resultado, "44"};
		}
		else {
			
			if(num1 != null)
				return new String [] {num1.image, Integer.toString(num1.kind)};
			else 
				return null;
		}
	}

	private Token termCheck(SimpleNode term) throws SemanticException {
		
		if(term == null) return null;
		
		String op = (term.value1 == null)? "None" : term.value1;
		
		Token result = new Token();
		
		Token[] num1 = null;
		if(term.jjtGetChild(0)!= null) {
			try {
				num1 = unaryexpCheck((SimpleNode)term.jjtGetChild(0));
			}catch(SemanticException e) {
				System.err.println(e.getMessage());
				foundSemanticError++;
			}
		}
		
		Token[] num2 = null;
		if(term.jjtGetNumChildren() > 1) {
			if(term.jjtGetChild(1)!= null) {
				try {
					num2 = unaryexpCheck((SimpleNode)term.jjtGetChild(1));
				}catch(SemanticException e) {
					System.err.println(e.getMessage());
					foundSemanticError++;
				}
			}
		}
		
		if(num2 != null) {
			if(num1[0].kind == num2[0].kind)
				throw new SemanticException("Os tipos de dados são incompativeis");
		}
		
		if(op.equals("*") && num2 != null) {
			
			if(num1[0].kind != 44) 
				throw new SemanticException("Multiplicacao nao pode ser feita com outro tipo alem de int");
			
			int num1_valor = Integer.parseInt(num1[0].image);
			int num2_valor = Integer.parseInt(num2[0].image);			
			
			if(num1[1] != null && num1[1].kind == 6) {
				num1_valor = -num1_valor;
			}
			
			if(num2[1] != null && num2[1].kind == 6) {
				num2_valor = -num2_valor;
			}
			
			int multiplicacao = num1_valor * num2_valor;
			
			result.kind = 44;
			result.image = Integer.toString(multiplicacao);
			
			return result;
		}
		else if(op.equals("/") && num2 != null) {
			
			if(num1[0].kind != 44) 
				throw new SemanticException("Divisao nao pode ser feita com outro tipo alem de int");
			
			int num1_valor = Integer.parseInt(num1[0].image);
			int num2_valor = Integer.parseInt(num2[0].image);	
			
			if(num2_valor == 0 && num1_valor == 0)
				throw new SemanticException("Divisao por 0 detectada");
			
			if(num1[1] != null && num1[1].kind == 6) {
				num1_valor = -num1_valor;
			}
			
			if(num2[1] != null && num2[1].kind == 6) {
				num2_valor = -num2_valor;
			}
			
			int divisao = num1_valor / num2_valor;
			
			result.kind = 44;
			result.image = Integer.toString(divisao);
			
			return result;
		}
		else {
			if(num1 != null) {
				if(num1[1] != null && num1[1].kind == 6) {
					int img = Integer.parseInt(num1[0].image);
					result.image = Integer.toString(-img);
					result.kind = num1[0].kind; 
					return result;
				}
				else {
					return num1[0];
				}
			}
			else return null;
		}
	}

	private Token[] unaryexpCheck(SimpleNode unary) throws SemanticException {
		
		String sinal = unary.value1;
			
		if(!sinal.equals("None")) {
			Token a = null; 
			try {
				a = factorCheck((SimpleNode)unary.jjtGetChild(0));
			}catch(SemanticException e) {
				System.err.println(e.getMessage());
				foundSemanticError++;
			}
			
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
				
				if(simbolos.getType(var.image).equals("int")) {
					result.kind = 44;
				}
				else if(simbolos.getType(var.image).equals("char")) {
					result.kind = 45;
				}
				else 
					result.kind = 46;
				
				result.image = simbolos.getValor(var.image);
				if(var.image.equals("None")) return null;
				else return result;
			}
		}
		else if(var.kind == 35) {
			
			String[] exp = null;
			try {
				exp = expressaoCheck((SimpleNode)jjtGetChild.jjtGetChild(0));
			}catch(SemanticException e) {
				System.err.println(e.getMessage());
				foundSemanticError++;
			}
			if(exp != null) {
				
				result.image = exp[0];
				if(exp[1] != null)
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
			String[] valor = null;
			try {
				valor = expressaoCheck((SimpleNode)filho.jjtGetChild(0));
			}catch(SemanticException e) {
				System.err.println(e.getMessage());
				foundSemanticError++;
			}
			if(valor != null) {
				if(valor[1] != null) {
					switch (filho.k.kind) {
						case 12:
							if(valor[1].equals(simbolos.getType(id)))
								simbolos.atualizaValor(id, valor[0]);
							else
								throw new SemanticException("Os tipos de dados são incompativeis");
							break;
						case 13:
							if(valor[1].equals(simbolos.getType(id))) {
								
								String res;
								
								int valor_1 = Integer.parseInt(valor[0]);
								String Svalor_2 = simbolos.getValor(id);
								int valor_2 = Integer.parseInt(Svalor_2);
								
								int resu_i = valor_1 + valor_2;
								res = Integer.toString(resu_i);
								
								simbolos.atualizaValor(id, res);
							}
							else
								throw new SemanticException("Os tipos de dados são incompativeis");
							break;
						case 14:
							if(valor[1].equals(simbolos.getType(id))) {
								
								String res;
								
								int valor_2 = Integer.parseInt(valor[0]);
								String Svalor_2 = simbolos.getValor(id);
								int valor_1 = Integer.parseInt(Svalor_2);
								
								int resu_i = valor_1 - valor_2;
								res = Integer.toString(resu_i);
								
								simbolos.atualizaValor(id, res);
							}
							else
								throw new SemanticException("Os tipos de dados são incompativeis");
							break;
						case 15:
							if(valor[1].equals(simbolos.getType(id))) {
								
								String res;
								
								int valor_1 = Integer.parseInt(valor[0]);
								String Svalor_2 = simbolos.getValor(id);
								int valor_2 = Integer.parseInt(Svalor_2);
								
								int resu_i = valor_1 * valor_2;
								res = Integer.toString(resu_i);
								
								simbolos.atualizaValor(id, res);
							}
							else
								throw new SemanticException("Os tipos de dados são incompativeis");
							break;
						case 16:
							if(valor[1].equals(simbolos.getType(id))) {
								
								String res;
								
								int valor_2 = Integer.parseInt(valor[0]);
								String Svalor_2 = simbolos.getValor(id);
								int valor_1 = Integer.parseInt(Svalor_2);
								
								if(valor_1 == 0 && valor_2 == 0) {
									throw new SemanticException("Divisao por 0 detectada!");
								}else{
									int resu_i = valor_1 / valor_2;
									res = Integer.toString(resu_i);
									
									simbolos.atualizaValor(id, res);
								}
							}
							else
								throw new SemanticException("Os tipos de dados são incompativeis");
							break;
					}
				}
			}
		}
	}

	private void whileCheck(SimpleNode filho, int pos) throws SemanticException {
		
		if(filho == null) return;
		
		if(filho.jjtGetNumChildren() > 0) {
			
			String [] exp = null;
			try {
				exp = expressaoCheck((SimpleNode)filho.jjtGetChild(0));
			}catch(SemanticException e) {
				System.err.println(e.getMessage());
				foundSemanticError++;
			}
			if(!exp[1].equals("int")) {
				throw new SemanticException("Condicao de While nao pertence ao tipo aceitavel(int)");
			}
			
			if(filho.jjtGetNumChildren()> 1) {
				func_bodyCheck((SimpleNode)filho.jjtGetChild(1),pos);
			}
		}
		
	}

	private void forCheck(SimpleNode filho, int pos) throws SemanticException {
		
		if(filho == null) return;
		
		if(filho.jjtGetNumChildren() > 0) {
			try {
				atribCheck((SimpleNode)filho.jjtGetChild(0));
			}catch(SemanticException e) {
				System.err.println(e.getMessage());
				foundSemanticError++;
			}
			
			if(filho.jjtGetNumChildren() > 1) {
				String [] exp = null;
				try {
					exp = expressaoCheck((SimpleNode)filho.jjtGetChild(1));
				}catch(SemanticException e) {
					System.err.println(e.getMessage());
					foundSemanticError++;
				}
				if(exp != null) {
					if(!exp[1].equals("int")) {
						throw new SemanticException("Condicao de FOR nao pertence ao tipo aceitavel(int)");
					}
				}
				
				if(filho.jjtGetNumChildren() > 2) {
					try {
						atribCheck((SimpleNode)filho.jjtGetChild(2));
					}
					catch(SemanticException e) {
						System.err.println(e.getMessage());
						foundSemanticError++;
					}
					if(filho.jjtGetNumChildren() > 3) {
						func_bodyCheck((SimpleNode)filho.jjtGetChild(3),pos);
					}
				}
			}
		}
		
	}

	private void ifCheck(SimpleNode filho, int pos) throws SemanticException {
		
		if(filho == null) return;
		
		if(filho.jjtGetNumChildren() > 0) {
			
			String [] exp = null; 
			
			try {
				exp = expressaoCheck((SimpleNode)filho.jjtGetChild(0));
			}catch(SemanticException e) {
				System.err.println(e.getMessage());
				foundSemanticError++;
			}
			if(exp != null) {
				if(!exp[1].equals("int")) {
					throw new SemanticException("Condicao do IF nao pertence ao tipo aceitavel(int)");
				}
			}
			
			if(filho.jjtGetNumChildren() > 1) {
				
				func_bodyCheck((SimpleNode)filho.jjtGetChild(1), pos);
				
				if(filho.jjtGetNumChildren() > 2) {
					
					func_bodyCheck((SimpleNode)filho.jjtGetChild(2), pos);
				}
			}
		}
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
	
	public void param_listCheck(SimpleNode param){
		
		if(param.jjtGetNumChildren() == 0) return;
		
		String tipo1 = null, nome1, tipo2 = null, nome2 = null;
		if(param.jjtGetChild(0) != null) {
			tipo1 = func_typeCheck((SimpleNode)param.jjtGetChild(0));
		}
		if(param.jjtGetChild(1) != null) {
			tipo2 = func_typeCheck((SimpleNode)param.jjtGetChild(1));
		}
		nome1 = param.value1;
		if(param.value2 != null) nome2 = param.value2;
		
		simbolos.add(new EntryTable(nome1, "id", "par", tipo1, "0", "Local"));
		if(nome2 != null) simbolos.add(new EntryTable(nome2, "id", "par", tipo2, "0", "Local"));
	}
}