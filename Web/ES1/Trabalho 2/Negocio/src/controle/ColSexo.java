package controle;

import java.sql.Connection;

import util.NegocioException;

public class ColSexo {
	
	public Connection con;
	
	public ColSexo(Connection connection) {

		con = connection;

	}
	
	public int obterSexoPorSigla(String sexo) throws NegocioException {
		int i = 0;
		if(sexo.equals("Masculino")) {
			i = 1;
		} else if(sexo.equals("Feminino")) {
			i = 2;
		} else {
			throw new NegocioException("Sigla invalidas");
		}
		return i;
	}
	
	public Connection getCon() {
		return con;
	}

	public void setCon(Connection con) {
		this.con = con;
	}
	
}