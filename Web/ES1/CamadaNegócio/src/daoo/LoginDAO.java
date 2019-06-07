package daoo;

import java.sql.Connection;

import sqll.Query;

public class LoginDAO {

	public static int verificaLogin(String login, String senha) throws Exception {
		
		Connection con = Query.getConnection();
		
		return Query.getLogin(con, login, senha);
	}
	
}
