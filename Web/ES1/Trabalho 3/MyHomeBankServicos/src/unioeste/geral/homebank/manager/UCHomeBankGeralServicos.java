package unioeste.geral.homebank.manager;

import java.sql.Connection;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;

import unioeste.apoio.MySQL.ConexaoBD;
import unioeste.geral.exception.*;
import unioeste.geral.homebank.bo.*;
import unioeste.geral.homebank.col.*;

public class UCHomeBankGeralServicos {

	private Connection con;
	
	public UCHomeBankGeralServicos() throws Exception {
		
		try {
			this.con = ConexaoBD.getConnection();
		} catch (Exception e) {

			e.printStackTrace();
		}
	}
	
	@SuppressWarnings("static-access")
	public int registrarTransferenciaBancaria(String correntista, String docCorre, String favorecido, String docFav, Date dataTrans, int conta,
			int favConta, int favBanco, int favAgencia, double valorTrans) throws NumberFormatException, Exception{
		
		Date atual = new Date(), tresDias, local;
		
		Calendar cal = Calendar.getInstance();
		cal.setTime(atual); // Objeto Date() do usuário
		cal.add(cal.DAY_OF_MONTH, +3);
		
		tresDias = cal.getTime();
		
		cal.setTime(atual);
		cal.add(cal.DAY_OF_MONTH, -1);
		
		local = cal.getTime();
		
		ColCliente colCli = new ColCliente(con);
		
		int idCli = colCli.validar(correntista, docCorre);
		
		if(idCli != 0) {
			
			ColContaBancaria colContBan = new ColContaBancaria(con);
			
			int idFav = colCli.validar(favorecido, docFav);
			
			if(idFav != 0) {
				
				if((dataTrans.after(local)) && dataTrans.before(tresDias)) {
					
					ColBanco colB = new ColBanco(con);
					
					int idBanco = colB.valida(favBanco);
					
					ColAgencia colA = new ColAgencia(con);
					
					int idAgencia = colA.valida(favAgencia);
					
					if(idBanco != 0 && idAgencia != 0) {
						
						ContaBancaria CorreConta = colContBan.getConta(conta);
						ContaBancaria FavConta = colContBan.getConta(favConta);
						
						if(valorTrans > 1.0 && valorTrans <= CorreConta.getSaldo()) {
							
							Motivo mt = new Motivo();
							mt.setIdMotivo(10);
							mt.setNomeMotivo("Transfêrencia Bancária");
							
							ColMovimentacao cLB = new ColMovimentacao(con);
							Movimentacao MoviCorrentista = new Movimentacao();
							int idMov = cLB.getMovNextID();
							
							MoviCorrentista.setDataMovimentacao(new java.sql.Date(dataTrans.getTime()));
							MoviCorrentista.setIdMovimentacao(idMov);
							MoviCorrentista.setMot(mt);
							MoviCorrentista.setValor(valorTrans);
							
							int correInseriu = cLB.insertLancamento(MoviCorrentista, CorreConta.getNroConta());
							
							if(correInseriu == 1) {
								colContBan.atualizaSaldo(CorreConta.getNroConta(), CorreConta.getSaldo()-valorTrans);
								
								Movimentacao MoviFavorecido = new Movimentacao();
								MoviFavorecido.setDataMovimentacao(new java.sql.Date(dataTrans.getTime()));
								MoviFavorecido.setIdMovimentacao(idMov+1);
								MoviFavorecido.setMot(mt);
								MoviFavorecido.setValor(valorTrans);
								
								int favInseriu = cLB.insertLancamento(MoviFavorecido, FavConta.getNroConta());
								
								if(favInseriu == 1) {
									colContBan.atualizaSaldo(FavConta.getNroConta(), FavConta.getSaldo()+valorTrans);
								
									return 1;
								}
								else
									throw new MovimentacaoException("A inserção da Movimentação na conta do Favorecido gerou um erro");
							}
							else
								throw new MovimentacaoException("A inserção da Movimentação na conta do Correntista gerou um erro");
						}
						else
							throw new MovimentacaoException("Valor de Transfêrencia é menor que R$ 1 ou maior que o saldo do Cliente");
					}
					
				}
				else
					throw new MovimentacaoException("Data Transferência não é igual ou superior (3 dias a mais) da data atual");
			}	
			else
				throw new ClienteException("Favorecido não Cadastrado");
		}
		else
			throw new ClienteException("Cliente não Cadastrado");
		
		return 0;
	}
	
	public ArrayList<String> consultarExtratoConta(String consultado, String docFav) throws ClienteException {
		
		ColCliente colC = new ColCliente(con);
		
		int idCli = colC.validar(consultado, docFav);
		
		if(idCli != 0) {
			
			ColContaBancaria colCB = new ColContaBancaria(con);
			
			ContaBancaria cb = null;
			try {
				cb = colCB.getConta(idCli);
			} catch (Exception e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			
			if(cb != null) {
		
				ColMovimentacao colLB = new ColMovimentacao(con);
				
				ArrayList<String> movimentacoes = null;
				try {
					movimentacoes = colLB.getLancamentos(cb.getNroConta());
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} 
				
				movimentacoes.add(String.valueOf(cb.getSaldo()));
				return movimentacoes;
			}
			else {
				throw new ClienteException("Conta Bancária do Cliente não cadastrada");
			}
		}
		else
			throw new ClienteException("Cliente não Valido");
	}
}
