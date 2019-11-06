package unioeste.geral.homebank.servicos;

import java.util.ArrayList;
import java.util.Date;

import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebService;

import unioeste.geral.homebank.manager.UCHomeBankGeralServicos;

@WebService(endpointInterface="unioeste.geral.homebank.servicos.HomeBank")
public class HomeBankImpl implements HomeBank{
	@Override
	@WebMethod
	public String[][] consultarExtratoConta(@WebParam(name="nome")String nome, @WebParam(name="doc")String doc) throws Exception {
		
		UCHomeBankGeralServicos ucHB = new UCHomeBankGeralServicos();
		
		ArrayList<String> cons = ucHB.consultarExtratoConta(nome, doc);
		
		String[][] param = new String[cons.size()/4+1][4];
		
		int i = 0, j = 0;
		
		for(String ind: cons) {
			if(i == cons.size()/4) break;
			param[i][j] = ind;
			if(j == 3) {
				j = 0;
				i++;
			}
			else j++;
		}
		
		param[cons.size()/4][0] = cons.get(cons.size()-1);
		
		for(String[] lin : param) {
			for(String col: lin) {
				System.out.println(col);
			}
		}
		
		return param;
	}
	@Override
	@WebMethod
	public int registrarTransferenciaBancaria(@WebParam(name="correntista")String correntista, @WebParam(name="docCorre")String docCorre, @WebParam(name="favorecido")String favorecido, @WebParam(name="docFav")String docFav,
			@WebParam(name="dataTrans")Date dataTrans, @WebParam(name="conta")int conta, @WebParam(name="favConta")int favConta, @WebParam(name="favBanco")int favBanco, 
			@WebParam(name="favAgencia")int favAgencia, @WebParam(name="valorTrans")double valorTrans) throws Exception {
		
		UCHomeBankGeralServicos ucHB = new UCHomeBankGeralServicos();
		
		int deuCerto = ucHB.registrarTransferenciaBancaria(correntista, docCorre, favorecido, docFav, dataTrans, conta, favConta, favBanco, favAgencia, valorTrans);
		
		return deuCerto;
	}
}
