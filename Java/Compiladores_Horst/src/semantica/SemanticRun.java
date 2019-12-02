package semantica;

import compiladorcc.SimpleNode;
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
		for(i = 0; i < root.jjtGetNumChildren()-1; i++) {
			
			func_listCheck((SimpleNode) root.jjtGetChild(i));
		}
		if(foundSemanticError != 0)
			throw new SemanticException (foundSemanticError + " Erros Semanticos encontrados");
	}
	
	public void func_listCheck(SimpleNode alvo){
		
		if(alvo == null) return;
		
		for(int i = 0; i < alvo.jjtGetNumChildren(); i++) {
			try {
				func_declCheck((SimpleNode)alvo.jjtGetChild(i));
			} catch (SemanticException e) {
				// TODO Auto-generated catch block
				System.err.println(e.getMessage());
				foundSemanticError++;
			}
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
		
		if(!nome_proc.equals("main")) {
			if(simbolos.find(nome_proc) == 0) {
				simbolos.add(new EntryTable(nome_proc, "id", "proc", retorno, "None", "Global"));
			}
			else
				throw new SemanticException("Função/Procedimento "+ nome_proc +" ja declarada");
		}
		
		if(alvo.jjtGetChild(1) != null) {
			try {
				param_listCheck((SimpleNode)alvo.jjtGetChild(1));
			}catch(SemanticException e) {
				System.err.println(e.getMessage());
				foundSemanticError++;
			}
		}
		
		if(alvo.jjtGetChild(2) != null) {
			func_bodyCheck((SimpleNode)alvo.jjtGetChild(2));
		}
		
		System.out.println(simbolos.toString());
		
		while(pos != simbolos.getPos())
			simbolos.retira();
		
		System.out.println(simbolos.toString());
	}
	  
	private void func_bodyCheck(SimpleNode body) {
		
		if(body == null) return;
		
		for(int i = 0; i < body.jjtGetNumChildren()-1; i++) {
			SimpleNode filho = (SimpleNode)body.jjtGetChild(i);
			try {
				switch(filho.jjtGetId()) {
					case 4:
						var_listCheck(filho);
						break;
					case 8:
						ifCheck(filho);
						break;
					case 9:
						switchCheck(filho);
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
						returnCheck(filho);
						break;
				}
			}catch(SemanticException e) {
				System.err.println(e.getMessage());
				foundSemanticError++;
			}
		}
	}

	private void returnCheck(SimpleNode filho) {
		// TODO Auto-generated method stub
		
	}

	private void atribCheck(SimpleNode filho) {
		// TODO Auto-generated method stub
		
	}

	private void whileCheck(SimpleNode filho) {
		// TODO Auto-generated method stub
		
	}

	private void forCheck(SimpleNode filho) {
		// TODO Auto-generated method stub
		
	}

	private void switchCheck(SimpleNode filho) {
		// TODO Auto-generated method stub
		
	}

	private void ifCheck(SimpleNode filho) {
		// TODO Auto-generated method stub
		
	}

	private void var_listCheck(SimpleNode filho) throws SemanticException {
		
		if(filho == null) return;
		
		String tipo = filho.value1;
		String nome = filho.value2;
		
		if(simbolos.find(nome) == 0) {
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
		
		simbolos.add(new EntryTable(nome1, "id", "par", tipo1, "0", "Global"));
		if(nome2 != null) simbolos.add(new EntryTable(nome2, "id", "par", tipo2, "0", "Global"));
	}
}