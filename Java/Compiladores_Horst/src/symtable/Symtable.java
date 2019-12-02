package symtable;

import java.util.ArrayList;

public class Symtable {

	private ArrayList<EntryTable> table;
	private int pos;

	public int getPos() {
		return pos;
	}

	public void setPos(int pos) {
		this.pos = pos;
	}

	public Symtable() {
		table = new ArrayList<EntryTable>();
		pos = 0;
	}
	
	public ArrayList<EntryTable> getTable() {
		return table;
	}

	public void setTable(ArrayList<EntryTable> table) {
		this.table = table;
	}
	
	public void add(EntryTable novaEntry) {
		
		table.add(novaEntry);
		pos++;
	}
	
	public void retira() {
		table.remove(pos-1);
		pos--;
	}

	public int find(String nome) {
		
		for(EntryTable a: table) {
			
			if(a.getCadeia().equals(nome)) {
				return 1;
			}
		}
		
		return 0;
	}

	public String getType(String nome) {
		
		for(EntryTable a: table) {
			if(a.getCadeia().equals(nome))
				return a.getTipo();
		}
		
		return "None";
	}
	
	public String toString() {
		String print = "pos = " + pos;
		
		for(EntryTable ind: table) {
			print += "\n[";
			print += ind.toString();
			print += "]";
		}
		
		return print;
	}
}
