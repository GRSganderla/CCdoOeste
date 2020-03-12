package sintatic.recovery;

import java.util.HashSet;
import java.util.Iterator;

import javacc.Anansi;

public class RecoverySet extends HashSet {

	/**
	 * construtor, cria um conjunto vazio
	 * @pre nenhum
	 * @pos conjunto vazio criado
	 */
	public RecoverySet() { //cria conjunto vazio
		super();
	}
	
	/**
	 * construtor, cria um conjunto com um elemento
	 * @param t, primeiro elemento a ser inserido 
	 * @pre nenhum
	 * @pos conjunto criado
	 */
	public RecoverySet(int t) { //cria conjunto com um tipo de token
		this.add(new Integer(t));
	}
	
	/**
	 * contains, verifica se o token pertence ao conjunto
	 * @param n, elemento a ser conferido
	 * @pre nenhum
	 * @pos nenhum
	 */
	public boolean contains (int t) { 
		return super.contains(new Integer(t));
	}
	
	
	/**
	 * union, faz a uni�o de dois conjuntos
	 * @param s, conjunto a ser feito a uni�o
	 * @pre nenhum
	 * @pos criado terceiro conjunto sem excluir nenhum
	 */
	public RecoverySet union (RecoverySet s) {
		RecoverySet t = null;
		if(s != null) {
			t = (RecoverySet) this.clone();
			t.addAll(s);
		}
		return t; // retorna um tercceiro conjunto sem excluir nenhum
	}
	
	/**
	 * remove, remove um elemento do conjunto
	 * @param n, elemento a ser removido
	 * @pre nenhum
	 * @pos elemento removido do conjunto
	 */
	public RecoverySet remove (int n) { //remove um elemento do conjunto
		RecoverySet t = (RecoverySet)this.clone();
		t.remove(new Integer(n));
		return t;
	}
	
	public String toString() {
		Iterator it = this.iterator();
		String s = "";
		int k;
		while(it.hasNext()) {
			k = ((Integer) it.next()).intValue();
			s += Anansi.im(k) + " ";
		}
		return s;
	}
}
