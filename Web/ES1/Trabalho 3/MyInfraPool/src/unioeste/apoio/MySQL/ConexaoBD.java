package unioeste.apoio.MySQL;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.util.ArrayList;
import org.apache.tomcat.dbcp.dbcp2.BasicDataSource;

public class ConexaoBD {
		
	public static BasicDataSource bd = new BasicDataSource();
	
	static {
		
		bd.setDriverClassName("com.mysql.cj.jdbc.Driver");
		bd.setUrl("jdbc:mysql://localhost:3306/homebank?useTimezone=true&serverTimezone=UTC");
		bd.setUsername("root");
		bd.setPassword("Guilherme1702");
		bd.setMinIdle(3);
		bd.setMaxIdle(15);
		bd.setMaxOpenPreparedStatements(150);
	}
	
	public static Connection getConnection() throws Exception{
		
		return bd.getConnection();
	}
	
	public static void insereSQLComand(Connection conn, String query) throws Exception
	{
		try {
			
			PreparedStatement create = conn.prepareStatement(query);
			create.executeUpdate();
			
		}catch(Exception e) {System.out.println(e);}
	}
	
	public static ArrayList<String> getTabela(Connection conn, String query) throws Exception
	{
		try {
			
			PreparedStatement stat = conn.prepareStatement(query);
			
			ResultSet res = stat.executeQuery();
			ArrayList<String> cliente = new ArrayList<String>();
			
			ResultSetMetaData rsmd = res.getMetaData();
			int colunas = rsmd.getColumnCount();
			
			while(res.next()) {
				for(int i = 1; i <= colunas; i++){
					
					cliente.add(res.getString(i));
				}
			}
			
			return cliente;
			
		}catch(Exception e) {
			
			System.out.println(e);
		}
		return null;	
	}
	
	public static String getSelect(Connection conn, String query) throws Exception
	{
		try {
			
			PreparedStatement stat = conn.prepareStatement(query);
			
			ResultSet res = stat.executeQuery();
			String cliente;
			
			res.next();
			
			cliente = res.getString(1);
			
			return cliente;
			
		}catch(Exception e) {
			System.out.println(e);
		}
		return null;	
	}
}
