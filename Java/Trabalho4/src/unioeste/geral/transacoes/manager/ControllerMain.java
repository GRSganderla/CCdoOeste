package unioeste.geral.transacoes.manager;

import java.io.IOException;
import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Random;
import java.util.Scanner;

import unioeste.apoio.MySQL.infra.*;
import unioeste.geral.exception.BDException;



public class ControllerMain {
	
	public static Scanner scan = new Scanner(System.in);
	
	public static int verificaCliente(Connection con, String nome) throws BDException {
		String res = null;
		ConexaoBD bdcon = new ConexaoBD();
		
		try {
			res = bdcon.getSelect(con, "SELECT idCliente FROM Cliente WHERE Nome LIKE '"+ nome +"';");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			System.err.println(e.getMessage());
		}
		
		if(res != null) {
			int idCliente = Integer.parseInt(res);
			return idCliente;
		}
		else {
			throw new BDException("Não existe registro de Cliente com esse nome: "+nome);
		}
	}
	
	public static void verificaConta(Connection con, int idCliente, int codConta, String nomeCliente) throws BDException {
		
		String res = null;
		ConexaoBD bd = new ConexaoBD();
		
		try {
			res = bd.getSelect(con, "SELECT 1 FROM Conta WHERE Cliente_idCliente="+ idCliente+" AND idConta="+ codConta +";");
		}
		catch(Exception e) {
			System.err.println(e.getMessage());
		}
		
		if(res == null) throw new BDException("Não existe registro de Conta com o numero "+codConta+" no cadastro do Cliente: "+ nomeCliente); 
	}
	
	public static void consultarSaldo(Connection conn) {
		
		System.out.println("-------------------------------------------------------");
		System.out.println("                 Consulta de Saldo");
		System.out.println("-------------------------------------------------------");
		System.out.println("Entre com os dados");
		
		System.out.print("Nome Pessoa Cadastrada: ");
		String nomeCliente = scan.nextLine();
		
		try {
			
			int idCliente = verificaCliente(conn, nomeCliente);
			
			System.out.print("Nro. Conta: ");
			int codConta = scan.nextInt();
			
			verificaConta(conn, idCliente, codConta, nomeCliente);
			
			getAllTransacoes(conn, codConta);	
		}
		catch(BDException e) {
			System.err.println(e.getMessage());
		}
	}
	
	public static void getGroups(Connection conn, String query) {
		try{
			String []coluna = {"Despesa", "Valor Total"};
			PreparedStatement stat = conn.prepareStatement(query);
			
			ResultSet res = stat.executeQuery();
			res.next();
			
			System.out.printf("\n %-20s ", coluna[0]);
			System.out.printf(" %-48s\n", coluna[1]);		
			
			double saldoDis = 0.0;
			double saldoRec = 0.0;
			
			do {
				
				System.out.printf(" %-22s ", (res.getString("nomeTipo").split(" ").length > 2)? res.getString("nomeTipo").split(" ")[2].toUpperCase() : res.getString("nomeTipo").split(" ")[1].toUpperCase());
				String tipo = res.getString("nomeTipo");
				System.out.printf("%6.2f\n", res.getDouble("SUM(valor)"));
				
				if(tipo.contains("Pagamento")) {
					saldoDis += res.getDouble("SUM(valor)");
				}
				else
					saldoRec += res.getDouble("SUM(valor)");
				
			}while(res.next());
			
			System.out.printf("\n %-30s %60.2f\n", "TOTAL DE DESPESAS", saldoDis);
			System.out.printf(" %-30s %60.2f\n", "TOTAL DE RECEITAS do Periodo", saldoRec);
		}
		catch(Exception e) {
			System.err.println(e.getMessage());
		}
	}
	
	public static void ConsultarDespesas(Connection con) {
		
		System.out.println("-------------------------------------------------------");
		System.out.println("           Consulta de Dispesas e Receitas");
		System.out.println("-------------------------------------------------------");
		System.out.println("Entre com os dados");
		
		System.out.print("Nome Pessoa Cadastrada: ");
		String nomeCliente = scan.nextLine();
		
		try {
			
			int idCliente = verificaCliente(con, nomeCliente);
			
			System.out.print("Nro. Conta(0 - Todas as Contas): ");
			int codConta = scan.nextInt();
			
			Calendar c1 = Calendar.getInstance(), c2 = Calendar.getInstance();
			System.out.print("Periodo(dd/mm/yyyy dd/mm/yyyy): ");
			
			scan.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");
			
			String linha = scan.nextLine();
			String []datas = linha.split(" ");
		    DateFormat df1=new SimpleDateFormat("dd/mm/yyyy");
		    DateFormat df2=new SimpleDateFormat("yyyy-mm-dd");
		    java.util.Date date1 = df1.parse(datas[0]);
		    java.util.Date date2 = df1.parse(datas[1]);
		    c1.setTime(date1);
		    c2.setTime(date2);
		    Date dat1 = new Date(c1.getTime().getTime());
		    Date dat2 = new Date(c2.getTime().getTime());
			
			String query;
			
			if(codConta == 0) {
				query ="select TipoReceitaDispesa.nomeTipo, SUM(valor) from receitadispesa, tiporeceitadispesa, Conta WHERE Conta.Cliente_idCliente="+idCliente
						      + " AND receitadispesa.Conta_idConta=Conta.idConta AND TipoReceitaDispesa_idTipoReceitaDispesa=tiporeceitadispesa.idTiporeceitaDispesa AND (receitadispesa.Data Between '"+df2.format(dat1)+"' AND '"+df2.format(dat2)+"') group by TipoReceitaDispesa_idTipoReceitaDispesa;";
				
			}
			else {
				verificaConta(con, idCliente, codConta, nomeCliente);
				query ="select TipoReceitaDispesa.nomeTipo, SUM(valor) from receitadispesa, tiporeceitadispesa, Conta WHERE Conta.Cliente_idCliente="+idCliente+" AND Conta.idConta="+codConta
					      + " AND receitadispesa.Conta_idConta=Conta.idConta AND TipoReceitaDispesa_idTipoReceitaDispesa=tiporeceitadispesa.idTiporeceitaDispesa AND (receitadispesa.Data Between '"+df2.format(dat1)+"' AND '"+df2.format(dat2)+"') group by TipoReceitaDispesa_idTipoReceitaDispesa;";
			}
			getGroups(con, query);
		}
		catch(BDException e) {
			System.err.println(e.getMessage());
		} catch (ParseException e) {
			e.printStackTrace();
		}
	}
	
	private static void getAllTransacoes(Connection conn, int codConta) {
		
		String query = "SELECT receitadispesa.Data, TipoReceitaDispesa.nomeTipo, receitadispesa.nomeOrigem, receitadispesa.nroDoc, receitadispesa.valor, Conta.saldo FROM Conta, receitadispesa, TipoReceitaDispesa WHERE Conta.idConta="+codConta+" AND receitadispesa.Conta_idConta=Conta.idConta AND receitadispesa.TipoReceitaDispesa_idTipoReceitaDispesa=tiporeceitadispesa.idTipoReceitaDispesa; \r\n";
		
		try{
			String []coluna = {"Data", "Tipo Receita/Dispesa", "nroDoc", "Valor", "Saldo"};
			PreparedStatement stat = conn.prepareStatement(query);
			
			ResultSet res = stat.executeQuery();
			res.next();
			double saldo = res.getDouble("saldo");
			System.out.println("Saldo Atual: "+ saldo);
			
			System.out.printf(" %-20s ", coluna[0]);
			System.out.printf(" %-48s ", coluna[1]);
			System.out.printf(" %-20s ", coluna[2]);
			System.out.printf(" %-19s ", coluna[3]);
			System.out.printf(" %-18s ", coluna[4]);
			System.out.println();		
			
			double saldoAtual = 0.0;
			
			do {
				
				System.out.printf(" %-20s ", res.getString("Data"));
				System.out.printf(" %-48s ", res.getString("nomeTipo")+" - "+ res.getString("nomeOrigem"));
				System.out.printf(" %-20d ", res.getInt("nroDoc"));
				String tipo = res.getString("nomeTipo");
				
				if(tipo.contains("Pagamento")) {
					saldoAtual -= res.getDouble("valor");
				}
				else
					saldoAtual += res.getDouble("valor");
				
				System.out.printf(" %-20.2f ", res.getDouble("valor"));
				System.out.printf("%5.2f\n", saldoAtual);
			}while(res.next());
			
			System.out.print("\n\t\t\t SALDO");
			System.out.printf("%92.2f\n", saldoAtual);
		}
		catch(Exception e) {
			System.err.println(e.getMessage());
		}
	}
	
	public static void main(String[] args) throws IOException {
		
		ConexaoBD conect = new ConexaoBD();
		
		Connection con = null;
		
		try {
			con = conect.getConnection();
			
			int escolha = 1;
			while(escolha != 0) {
				System.out.println("Menu de Receita/Dispesa");
				System.out.println("1 - Realizar Transação");
				System.out.println("2 - Consultar Saldo");
				System.out.println("3 - Consultar Despesas");
				System.out.println("0 - Sair");
				
				System.out.print("Escolha: ");
				escolha = scan.nextInt();

				scan.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");
				
				switch(escolha) {
				
				case 1:
					realizarTransacao(con);
					break;
				case 2:
					consultarSaldo(con);
					break;
				case 3:
					ConsultarDespesas(con);
					break;
				case 0:
					scan.close();
					System.exit(0);
					break;
				}
				
				scan.nextLine();
			}
			
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public static void tabela() {
		System.out.println("  Id Tipo Receita/Despesa  |           Nome do Tipo         |");
		System.out.println("           1               |       Recebimento Salário      |");
		System.out.println("           2               |       Recebimento Aluguel      |");
		System.out.println("           3               | Recebimento Comissão de Vendas |");
		System.out.println("           4               |     Recebimento Pro-Labore     |");
		System.out.println("           5               |        Pagamento de Água       |");
		System.out.println("           6               |        Pagamento de Luz        |");
		System.out.println("           7               |      Pagamento de Telefone     |");
		System.out.println("           8               |    Pagamento de Supermercado   |");
		System.out.println("           9               |      Pagamento de Gasolina     |");
		System.out.println("          10               |     Pagamento de Assinatura    |");
		System.out.println("          11               |     Pagamento de Alimentação   |");
		System.out.println("          12               |        Pagamento de Saúde      |");
	}

	private static void realizarTransacao(Connection con) {
	
		ConexaoBD bd = new ConexaoBD();
		int escolha = 1;
		try {
			con.setAutoCommit(false);
			
			while(escolha != 0) {
				
				System.out.println("Menu de Transação");
				System.out.println("1 - Realizar Transação OK");
				System.out.println("2 - Realizar Transação Sem Commit ou Rollback");
				System.out.println("3 - Realizar Transação com Rollback");
				System.out.println("0 - Voltar");
				
				System.out.print("Escolha: ");
				escolha = scan.nextInt();
				
				if(escolha == 0) return;
				
				scan.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");
				
				System.out.println("Entre com os dados");
				
				System.out.print("Nome Pessoa Cadastrada: ");
				String nomeCliente = scan.nextLine();
				
				int idCliente = verificaCliente(con, nomeCliente);
				
				System.out.print("Nro. Conta: ");
				int codConta = scan.nextInt();

				scan.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");
				
				verificaConta(con, idCliente, codConta, nomeCliente);
				
				tabela();
				System.out.print("Tipo: ");
				int tipo = scan.nextInt();

				scan.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");
				
				if(tipo < 0 && tipo > 12) {
					throw new BDException("Tipo de Receita ou Despesa foi selecionado errado");
				}
				
				System.out.print("Valor da Receita/Despesa: ");
				double valor = scan.nextDouble();
				
				scan.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");
				
				System.out.print("Nome de Origem da Receita/Despesa: ");
				String nome = scan.nextLine();
				
				System.out.print("Data de Transação: ");
				String linha = scan.nextLine();

				Calendar c = Calendar.getInstance();
			    DateFormat df1=new SimpleDateFormat("dd/mm/yyyy");
			    DateFormat df2=new SimpleDateFormat("yyyy-mm-dd");
			    java.util.Date date1 = df1.parse(linha);
			    c.setTime(date1);
			    Date dat1 = new Date(c.getTime().getTime());
			    
			    Random rand = new Random();
			    int ran = rand.nextInt()%1000;
			    int id = bd.ultimoId(con, "SELECT MAX(nroDoc) FROM receitadispesa;") + ((ran < 0)? ran*-1: ran);
			    
				if(escolha == 1) {
					
					String query = "INSERT INTO receitadispesa(nroDoc, Data, valor, nomeOrigem, TipoReceitaDispesa_idTipoReceitaDispesa, Conta_idConta) VALUES (" +
							id + ",'"+ df2.format(dat1) +"',"+valor+", '"+ nome +"',"+ tipo +","+ codConta+");";
					bd.insereSQLComand(con, query);
					
					String update;
					
					if(tipo < 5)
						update = "UPDATE Conta SET saldo = saldo + "+ valor +" WHERE (`idConta` = '"+codConta+"');";
					else {
						update = "UPDATE Conta SET saldo = saldo - "+ valor +" WHERE (`idConta` = '"+codConta+"');";
					}
					bd.insereSQLComand(con, update);
					
					con.commit();
					System.out.println("OK!");
				}
				else if(escolha == 2) {
					
					String query = "INSERT INTO receitadispesa(nroDoc, Data, valor, nomeOrigem, TipoReceitaDispesa_idTipoReceitaDispesa, Conta_idConta) VALUES (" +
							id + ",'"+ df2.format(dat1) +"',"+valor+", '"+ nome +"',"+ tipo +","+ codConta+");";
					bd.insereSQLComand(con, query);
					
					String update;
					if(tipo < 5)
						update = "UPDATE Conta SET saldo = saldo + "+ valor +" WHERE (`idConta` = '"+codConta+"');";
					else {
						update = "UPDATE Conta SET saldo = saldo - "+ valor +" WHERE (`idConta` = '"+codConta+"');";
					}
					bd.insereSQLComand(con, update);
				}
				else if(escolha == 3) {
					try{
						String query = "INSERT INTO receitadispesa(nroDoc, Data, valor, nomeOrigem, TipoReceitaDispesa_idTipoReceitaDispesa, Conta_idConta) VALUES (" +
								id + ",'"+ df2.format(dat1) +"',"+valor+","+ tipo +","+ codConta+");";
						bd.insereSQLComand(con, query);
						
						String update;
						if(tipo < 5)
							update = "UPDATE Conta SET saldo = saldo + "+ valor +" WHERE (`idConta` = '"+codConta+"');";
						else {
							update = "UPDATE Conta SET saldo = saldo - "+ valor +" WHERE (`idConta` = '"+codConta+"');";
						}
						
						bd.insereSQLComand(con, update);
						System.out.println("Transação feita!");
					}catch(SQLException e) {
						con.rollback();
						System.err.println(e.getMessage());
					}
				}
				else if(escolha == 4) {
					String query = "INSERT INTO receitadispesa(nroDoc, Data, valor, nomeOrigem, TipoReceitaDispesa_idTipoReceitaDispesa, Conta_idConta) VALUES (" +
							id + ",'"+ df2.format(dat1) +"',"+valor+", '"+ nome +"',"+ tipo +","+ codConta+");";
					bd.insereSQLComand(con, query);
					String update;
					if(tipo < 5)
						update = "UPDATE Conta SET saldo = saldo + "+ valor +" WHERE (`idConta` = '"+codConta+"');";
					else {
						update = "UPDATE Conta SET saldo = saldo - "+ valor +" WHERE (`idConta` = '"+codConta+"');";
					}
					
					bd.insereSQLComand(con, update);
					con.rollback();
				}
				else {
					System.err.println("OPÇÃO ERRADA!");
				}
				
			}
		} catch (SQLException e) {
			System.err.println(e.getMessage());
		} catch (BDException e) {
			System.err.println(e.getMessage());
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
