package sintatic.recovery;

import javacc.AnansiConstants;

//implementa os conjuntos first para alguns n�o-terminais
public class First {
	static public final RecoverySet varlist = new RecoverySet();
	static public final RecoverySet functlist = new RecoverySet();
	static public final RecoverySet functbody = new RecoverySet();
	static public final RecoverySet program = functlist;
	
	/**
	 * Adiciona os terminais da rela�ao primeiro no conjunto de sincroniza��o
	 */
	static {
		varlist.add(new Integer(AnansiConstants.VOID));
		varlist.add(new Integer(AnansiConstants.INT));
		varlist.add(new Integer(AnansiConstants.CHAR));
		
		functlist.add(new Integer(AnansiConstants.VOID));
		functlist.add(new Integer(AnansiConstants.INT));
		functlist.add(new Integer(AnansiConstants.CHAR));
		functlist.add(new Integer(AnansiConstants.IDENT));
		
		functbody.addAll(varlist);
		functbody.add(new Integer(AnansiConstants.IF));
		functbody.add(new Integer(AnansiConstants.SWITCH));
		functbody.add(new Integer(AnansiConstants.FOR));
		functbody.add(new Integer(AnansiConstants.WHILE));
		functbody.add(new Integer(AnansiConstants.IDENT));
		functbody.add(new Integer(AnansiConstants.BREAK));
		functbody.add(new Integer(AnansiConstants.RETURN));
	}

}
