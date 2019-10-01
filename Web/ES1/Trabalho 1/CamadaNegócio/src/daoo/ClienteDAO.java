package daoo;

import java.sql.Connection;
import java.util.ArrayList;

import modeloss.Cliente;
import sqll.Query;

public class ClienteDAO {

	private static final String NULL = null;

	public static boolean validaCPF(String cpf) {
		if(cpf == NULL) return true;
		if(cpf.length() < 11) return false;
		return (cpf.matches("[0-9]{3}(.)*[0-9]{3}(.)*[0-9]{3}(-)*[0-9]{2}"));
	}
	public static boolean validaCNPJ(String cnpj) {
		if(cnpj == NULL) return true;
		if(cnpj.length() < 18) return false;
		return (cnpj.matches("[0-9]{2}.[0-9]{3}.[0-9]{3}/[0-9]{4}-[0-9]{2}"));
	}
	public static boolean validaNome(String nome) {
		if(nome.length() < 2 || nome == NULL) return false;
		
		return (nome.matches("[a-zA-Z]{2,}( [a-zA-Z]{2,})*"));
	}
	public static boolean validaCEP(String cep) {
		if(cep.length() < 8) return false;
		return (cep.matches("[0-9]{5}-[0-9]{3}"));
	}
	public static boolean validaEmail(String email) {
		return (email.matches("^[_A-Za-z0-9-\\+]+(\\.[_A-Za-z0-9-]+)*@[A-Za-z0-9-]+(\\.[A-Za-z0-9]+)*(\\.[A-Za-z]{2,})$"));
	}
	public static boolean validaFone(String fone) {
		if(fone.length() < 8) return false;
		return (fone.matches("(\\([0-9]{2}\\))*(9)*[0-9]{4}(-)*[0-9]{4}"));
	}
	public static String fazDataSQL(int dia, int mes, int ano) {
		return (ano + "-" + mes + "-" + dia);
	}
	
	public static Cliente getCliente(int attribute) throws Exception {
		
		if(attribute == 0) return null;
		
		Connection con = Query.getConnection();
		ArrayList<String> cliente = Query.getTabela(con, "SELECT * FROM cliente WHERE cliente.idCliente = '"+ attribute + "';");
		
		Cliente cadastrado = new Cliente(cliente);
		
		return cadastrado;
	}
	
public static boolean validaCliente(Cliente c) {
			
		if( 0 == c.getIdCliente() || !validaCPF(c.getCPF()) ||  !validaCNPJ(c.getCNPJ()) || !validaNome(c.getNome()) || !validaCEP(c.getCEP()) || !validaEmail(c.getEmail())) {
			return false;
		}
		if((c.getCPF() == NULL && c.getCNPJ() == NULL )|| (c.getCPF() != NULL && c.getCNPJ() != NULL) || c.getCEP() == NULL || c.getNum() == 0 || c.getEmail() == NULL || c.getSenha() == NULL || c.getIdCliente() == 0)
			return false;

		return true;
		
	}
	
	public static void insereCliente(Cliente c, int endereco) throws Exception {
		Connection con = Query.getConnection();
		int idProx;
		int id = Query.getId(con, "SELECT idCliente FROM cliente WHERE Nome = '"+ c.getNome()+"' AND '"+c.getEmail()+"' = Email ;");

		if(id == 0) {
			idProx = Query.getId(con, "SELECT MAX(idCliente) FROM cliente")+ 1;
			Query.insertSQLComand(con, "INSERT INTO cliente VALUES "
					+ "('"+idProx+"', '"+c.getNome()+"', '"+c.getCNPJ()+"', '"+c.getCPF()+"', '"+c.getEmail()+"', '"+c.getSenha()+"', '"+c.getNum()+"', '"+c.getComplemento()+"', '"+c.getCEP()+"', '"+endereco+"');");
			id = idProx; 
			c.setIdCliente(id);
		}
	}
	
	public static boolean validaSenha(String Senha) {
		if(Senha == NULL || Senha =="" || Senha.length() < 2) return false;
		return true;
	}
	
	public static void alteraCliente(Cliente c) throws Exception {
		
		Connection con = Query.getConnection();
		Query.insertSQLComand(con, "UPDATE cliente SET Senha = '"+c.getSenha()+"' WHERE idCliente = '"+ c.getIdCliente()+ "';");
		Query.insertSQLComand(con, "UPDATE cliente SET CEP = '"+c.getCEP()+"' WHERE idCliente = '"+ c.getIdCliente()+ "';");
		Query.insertSQLComand(con, "UPDATE cliente SET idEndereço = '"+c.getEndereco()+"' WHERE idCliente = '"+ c.getIdCliente()+ "';");
		Query.insertSQLComand(con, "UPDATE cliente SET NúmeroCasa = '"+c.getNum()+"' WHERE idCliente = '"+ c.getIdCliente()+ "';");
		Query.insertSQLComand(con, "UPDATE cliente SET Complemento = '"+c.getComplemento()+"' WHERE idCliente = '"+ c.getIdCliente()+ "';");
	}
}
