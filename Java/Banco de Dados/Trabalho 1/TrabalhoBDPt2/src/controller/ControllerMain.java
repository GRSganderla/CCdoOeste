package controller;
import java.sql.Connection;

import comandosSQL.funcoesSQL;

public class ControllerMain {

	public static void main(String[] args) throws Exception {
		
		Connection con = funcoesSQL.getConnection("jdbc:mysql://localhost:3308/trabalho3?autoReconnect=true&useSSL=false");
		//a)
		//ControllerMain.insertDiscEProf1(con);
		funcoesSQL.select(con, "SELECT codDisciplina, nomeDisc, prof1.codProf, nomeProf FROM disciplina1, prof1 WHERE disciplina1.codProf = prof1.codProf;");
		//b)
		//ControllerMain.insertDiscEProf2(con);
		funcoesSQL.select(con, "SELECT disciplina2.codDisc, nomeDisc, anoLetivo, dtInicioDisc, prof2.codProf, nomeProf FROM disciplina2, prof2, discProf2 "
				+ "WHERE disciplina2.codDisc = discProf2.codDisc AND discProf2.codProf = prof2.codProf");
		
		con.close();
	}
	
	@SuppressWarnings("unused")
	private static void insertDiscEProf1(Connection con) throws Exception {

		funcoesSQL.insertSQLComand(con, "INSERT INTO disciplina1 VALUES ('1', 'Banco de Dados', '1')");
		funcoesSQL.insertSQLComand(con, "INSERT INTO prof1 VALUES ('1', 'João da Siva Junior')");
		funcoesSQL.insertSQLComand(con, "INSERT INTO disciplina1 VALUES ('2', 'Banco de Dados', '2')");
		funcoesSQL.insertSQLComand(con, "INSERT INTO prof1 VALUES ('2', 'Roberto Gil')");
	}

	private static void insertDiscEProf2(Connection con) throws Exception {

		funcoesSQL.insertSQLComand(con, "INSERT INTO disciplina2 VALUES ('1', 'Banco de Dados');");
		funcoesSQL.insertSQLComand(con, "INSERT INTO discProf2 VALUES ('1', '1', '1', '2015', '2015-02-17'), ('2', '1', '2', '2018', '2018-02-25');");
		funcoesSQL.insertSQLComand(con, "INSERT INTO prof2 VALUES ('1', 'João da Siva Junior'), ('2', 'Roberto Gil');");
	}
}
