package unioeste.geral.homebank.servicos;

import java.util.Date;

import javax.jws.WebMethod;
import javax.jws.WebService;

@WebService
public interface HomeBank {
	@WebMethod
	public String[][] consultarExtratoConta(String nome, String doc) throws Exception;
	@WebMethod
	public int registrarTransferenciaBancaria(String correntista, String docCorre, String favorecido, String docFav, Date dataTrans, int conta,
			int favConta, int favBanco, int favAgencia, double valorTrans) throws Exception;
}
