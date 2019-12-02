package recovery;

import compiladorcc.SubLing_CConstants;

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
		varlist.add(new Integer(SubLing_CConstants.VOID));
		varlist.add(new Integer(SubLing_CConstants.INT));
		varlist.add(new Integer(SubLing_CConstants.CHAR));
		
		functlist.add(new Integer(SubLing_CConstants.VOID));
		functlist.add(new Integer(SubLing_CConstants.INT));
		functlist.add(new Integer(SubLing_CConstants.CHAR));
		functlist.add(new Integer(SubLing_CConstants.IDENT));
		
		functbody.addAll(varlist);
		functbody.add(new Integer(SubLing_CConstants.IF));
		functbody.add(new Integer(SubLing_CConstants.SWITCH));
		functbody.add(new Integer(SubLing_CConstants.FOR));
		functbody.add(new Integer(SubLing_CConstants.WHILE));
		functbody.add(new Integer(SubLing_CConstants.IDENT));
		functbody.add(new Integer(SubLing_CConstants.BREAK));
		functbody.add(new Integer(SubLing_CConstants.RETURN));
	}

}
