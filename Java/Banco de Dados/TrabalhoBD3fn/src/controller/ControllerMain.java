package controller;
import java.sql.Connection;
import java.util.ArrayList;
import java.util.Scanner;

import comandosSQL.funcoesSQL;

public class ControllerMain {

	public static void main(String[] args) throws Exception {
		Connection con = funcoesSQL.getConnection("jdbc:mysql://localhost:3308/trabalho2?autoReconnect=true&useSSL=false");
		int opcao = 1;
		String nomeCurso;
		boolean inserirJS1 = true, inserirJS2 = true;
		//ControllerMain.insertCursos(con);
		//ControllerMain.insertDisc(con);
		//ControllerMain.insertPessoas(con);
		Scanner scan = new Scanner(System.in);
		
		while(opcao != 0) {
			
			System.out.println("\n1 - Mostrar ao futuro aluno quais os cursos dispon�veis");
			System.out.println("2 - Mostrar ao futuro aluno quais as disciplinas dispon�veis para um determinado cursos");
			System.out.println("3 - Mostrar quais os alunos j� cadastrados, por�m ainda n�o matriculados em nenhum curso");
			System.out.println("4 - Mostrar uma matr�cula do aluno realizada");
			System.out.println("5 - Listar todos os alunos que est�o matriculados na disciplina de Banco de Dados.");
			System.out.println("6 - Algoritmo para impedir de matricular um aluno. Matricular o aluno �Jos� da Silva Lima�, por�m com o nome �Jos� S. Lima�");
			System.out.println("7 - Mostrar tabela");
			System.out.println("0 - Sair");
			System.out.print("Op��o: ");
			
			opcao = scan.nextInt();
			nomeCurso = scan.nextLine();
			
			switch(opcao) {
			case 1:
				funcoesSQL.select(con, "SELECT nomeCurso, siglaCurso FROM curso;");
				break;
			case 2:
				System.out.print("Entre com o determinado curso: ");
				nomeCurso = scan.nextLine();
				System.out.println(nomeCurso);
				funcoesSQL.select(con, "SELECT nomeDisc FROM disciplina, curso where disciplina.idCurso = curso.idCurso AND curso.nomeCurso = '" + nomeCurso + "';");
				break;
			case 3:
				funcoesSQL.select(con, "SELECT nome, cpf, fone, email FROM aluno where codAluno NOT IN (SELECT codAluno FROM matalunocurso);");
				break;
			case 4:
				funcoesSQL.select(con, "SELECT DISTINCT(aluno.nome), matalunocurso.dataMat, curso.nomeCurso, matalunoanoletivo.anoLetivo, disciplina.nomeDisc, discprof.dataInicio, professor.nomeProf FROM aluno, matalunocurso, matalunoanoletivo, matalunodisc, professor, curso, disciplina, discprof"
						+ " where aluno.nome like 'J%' AND aluno.codAluno = matalunocurso.codAluno AND matalunoanoletivo.codMat = matalunocurso.codMat AND matalunocurso.idCurso = curso.idCurso AND matalunodisc.matalunoanolet = matalunoanoletivo.codMatAno"
						+ " AND disciplina.codDisc = matalunodisc.codDisc AND disciplina.codDisc = discprof.codDisc AND professor.codProf = discprof.codProf Limit 3");
				break;
			case 5:
				funcoesSQL.select(con, "SELECT aluno.nome, disciplina.nomeDisc FROM aluno, matalunocurso, curso, disciplina "
						+ "where aluno.codAluno = matalunocurso.codAluno AND  curso.idCurso = matalunocurso.idCurso AND disciplina.idCurso = curso.idCurso AND disciplina.nomeDisc = 'Banco de Dados';");
				break;
			case 6: 
				ArrayList<String> nomeAluno = funcoesSQL.getLinha(con, "SELECT DISTINCT nome FROM aluno;");
				for(int i = 0, n = nomeAluno.size(); i < n; i++) {
					if(nomeAluno.get(i).equals("Jos� da Silva Lima"))
						inserirJS2 = false;
					if(nomeAluno.get(i).equals("Jos� S. Lima"))
						inserirJS1 = false;
				}
				System.out.print("\nInserindo Jos� S. Lima: ");
				if(inserirJS1) { 
					funcoesSQL.insertSQLComand(con, "INSERT INTO aluno (codAluno, nome, cpf, fone, email) VALUES ('8', 'Jos� S. Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com');");
					System.out.print("INSERIDO");
				}
				else
					System.out.println("N�o INSERIDO");
				
				System.out.print("\nInserindo Jos� da Silva Lima: ");
				if(inserirJS2) { 
					funcoesSQL.insertSQLComand(con, "INSERT INTO aluno (codAluno, nome, cpf, fone, email) VALUES ('8', 'Jos� da Silva Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com');");
					System.out.println("INSERIDO");
				}
				else
					System.out.println("N�o INSERIDO");
				
				funcoesSQL.select(con, "SELECT * FROM aluno;");
				break;
			case 7:
				funcoesSQL.select(con, "SELECT DISTINCT(aluno.nome), matalunocurso.dataMat, curso.nomeCurso, matalunoanoletivo.anoLetivo, disciplina.nomeDisc, discprof.dataInicio, professor.nomeProf FROM aluno, matalunocurso, matalunoanoletivo, matalunodisc, professor, curso, disciplina, discprof"
						+ " where aluno.codAluno = matalunocurso.codAluno AND matalunoanoletivo.codMat = matalunocurso.codMat AND matalunocurso.idCurso = curso.idCurso AND matalunodisc.matalunoanolet = matalunoanoletivo.codMatAno"
						+ " AND disciplina.codDisc = matalunodisc.codDisc AND disciplina.codDisc = discprof.codDisc AND professor.codProf = discprof.codProf");
				break;
			default:
			case 0:
				break;
			}
				
		} 
		
		//funcoesSQL.insertSQLComand(con, "DELETE FROM aluno where nome = 'Jos� S. Lima'; ");
		scan.close();
		con.close();
	}

	@SuppressWarnings("unused")
	private static void insertCursos(Connection con) throws Exception {
		
		funcoesSQL.insertSQLComand(con, "INSERT INTO curso VALUES ( '1', 'Ci�ncia da computa��o', 'CC'),('2','Engenharia El�trica', 'EE'),('3', 'Engenharia Mec�nica', 'EM'),('4', 'Matem�tica', 'MAT');");
	}

	@SuppressWarnings("unused")
	private static void insertDisc(Connection con) throws Exception {
		
		funcoesSQL.insertSQLComand(con, "INSERT INTO disciplina (nomeDisc, idCurso) VALUES"
				+ "('C�lculo Diferencial e Integral', '1'),"
				+ "('Computa��o I', '1'),"
				+ "('F�sica Geral  e Eletricidade B�sica', '1'),"
				+ "('Geometria Anal�tica e �lgebra Linear', '1'),"
				+ "('Introdu��o � Ci�ncia da Computa��o','1'),"
				+ "('L�gica e Matem�tica Discreta','1'),"
				+ "('Probabilidade e Estat�stica', '1'),"
				+ "('Algoritmos e Estrutura de Dados', '1'),"
				+ "('C�lculo Num�rico', '1'),"
				+ "('Computa��o II', '1'),"
				+ "('Conceitos de Linguagens de Programa��o', '1'),"
				+ "('Introdu��o � Arquitetura de Computadores', '1'),"
				+ "('Introdu��o � Engenharia de Software', '1'),"
				+ "('Linguagens Formais e Aut�matos', '1'),"
				+ "('Sistemas Digitais', '1'),"
				+ "('T�cnicas de Reda��o e Metodologia Cient�fica', '1'),"
				+ "('Banco de Dados', '1'),"
				+ "('Compiladores', '1'),"
				+ "('Engenharia de Software I', '1'),"
				+ "('Est�gio Supervisionado', '1'),"
				+ "('Forma��o Empreendedora', '1'),"
				+ "('Organiza��o e Arquitetura de Computadores','1'),"
				+ "('Projeto e An�lise de Algoritmos','1'),"
				+ "('Redes de Computadores','1'),"
				+ "('Sistemas Operacionais', '1'),"
				+ "('Computa��o Gr�fica', '1'),"
				+ "('Engenharia de Software II', '1'),"
				+ "('Intelig�ncia Artificial', '1'),"
				+ "('Optativa I', '1'),"
				+ "('Optativa II', '1'),"
				+ "('Processamento de Imagens Digitais', '1'),"
				+ "('Sistemas de Informa��o', '1'),"
				+ "('Sistemas Distribu�dos', '1'),"
				+ "('Trabalho de Conclus�o de Curso', '1');");
		funcoesSQL.insertSQLComand(con, "INSERT INTO disciplina (nomeDisc, idCurso) VALUES"
				+ "('Fundamentos da Matem�tica', '4'),"
				+ "('Geometria Anal�tica', '4'),"
				+ "('Geometria Euclidiana', '4'),"
				+ "('Inform�tica Aplicada � Educa��o Matem�tica', '4'),"
				+ "('Matem�tica B�sica', '4'),"
				+ "('Tend�ncias em Educa��o Matem�tica', '4'),"
				+ "('C�lculo I', '4'),"
				+ "('Desenho Geom�trico', '4'),"
				+ "('Did�tica Aplicada ao Ensino da Matem�tica', '4'),"
				+ "('Laborat�rio de Ensino de Matem�tica', '4'),"
				+ "('Libras', '4'),"
				+ "('Psicologia Aplicada � Educa��o Matem�tica', '4'),"
				+ "('Trigonometria e N�meros Complexos', '4'),"
				+ "('�lgebra Linear', '4'),"
				+ "('C�lculo II', '4'),"
				+ "('Estat�stica', '4'),"
				+ "('Estruturas Alg�bricas', '4'),"
				+ "('Est�gio Supervisionado I', '4'),"
				+ "('Introdu��o ao Trabalho Cient�fico', '4'),"
				+ "('Optativa', '4'),"
				+ "('Pol�ticas Educacionais', '4'),"
				+ "('An�lise Real', '4'),"	
				+ "('C�lculo III', '4'),"
				+ "('Est�gio Supervisionado II', '4'),"
				+ "('F�sica', '4'),"
				+ "('Hist�ria e Filosofia da Matem�tica', '4'),"
				+ "('Monografia', '4'),"
				+ "('M�todos Num�ricos', '4');");
		funcoesSQL.insertSQLComand(con, "INSERT INTO disciplina (nomeDisc, idCurso) VALUES"
				+ "('Computa��o', '2'),"
				+ "('C�lculo', '2'),"
				+ "('Desenho T�cnico', '2'),"
				+ "('F�sica I', '2'),"
				+ "('Geometria Anal�tica e �lgebra Linear', '2'),"
				+ "('Introdu��o � Engenharia El�trica', '2'),"
				+ "('Laborat�rio de F�sica', '2'),"
				+ "('Qu�mica Tecnol�gica e Materiais El�tricos', '2'),"
				+ "('Circuitos El�tricos', '2'),"
				+ "('C�lculo Vetorial e Vari�veis Complexas', '2'),"
				+ "('Equa��es Diferenciais', '2'),"
				+ "('F�sica II', '2'),"
				+ "('Laborat�rio de Instrumenta��o', '2'),"
				+ "('Mec�nica Geral', '2'),"
				+ "('Probabilidades e Estat�stica', '2'),"
				+ "('An�lise de Sistemas Din�micos', '2'),"
				+ "('C�lculo Num�rico', '2'),"
				+ "('Eletromagnetismo e Convers�o Eletromec. de Energia', '2'),"
				+ "('Eletr�nica B�sica', '2'),"
				+ "('Energia, Meio Ambiente e Desenvolvimento Sust.', '2'),"
				+ "('Engenharia de Seguran�a, Legisla��o e �tica Prof.', '2'),"
				+ "('Fen�menos de Transportes', '2'),"
				+ "('Medidas El�tricas e Metrologia', '2'),"
				+ "('Sistemas Digitais e Microprocessadores', '2'),"
				+ "('T�cnicas de Reda��o e Metodologia Cient�fica', '2'),"
				+ "('Controle Discreto', '2'),"
				+ "('Eletricidade Industrial', '2'),"
				+ "('Eletr�nica de Pot�ncia e Sistemas Industriais', '2'),"
				+ "('Engenharia Econ�mica e Gest�o de Projetos', '2'),"
				+ "('Introdu��o aos Sistemas de Energia El�trica', '2'),"
				+ "('Laborat�rio de Aplica��es de Microcontraladores', '2'),"
				+ "('M�quinas El�tricas e Acionamento', '2'),"
				+ "('Sistemas de Controle', '2'),"
				+ "('Comunica��o Anal�gica e Digital', '2'),"
				+ "('Est�gio Supervisionado', '2'),"
				+ "('Trabalho de Conclus�o de Curso', '2');");
		funcoesSQL.insertSQLComand(con, "INSERT INTO disciplina (nomeDisc, idCurso)  VALUES"
				+ "('C�lculo I', '3')," 
				+ "('Desenho T�cnico', '3')," 
				+ "('F�sica I', '3'),"
				+ "('Geometria Anal�tica e �lgebra Linear', '3')," 
				+ "('Introdu��o � Engenharia Mec�nica', '3')," 
				+ "('Laborat�rio de F�sica I', '3')," 
				+ "('Qu�mica', '3')," 
				+ "('T�cnicas de Reda��o Cient�fica', '3')," 
				+ "('Computa��o', '3')," 
				+ "('C�lculo II', '3')," 
				+ "('Equa��es Diferenciais', '3')," 
				+ "('F�sica II', '3')," 
				+ "('Laborat�rio de F�sica II', '3')," 
				+ "('Materiais de Constru��o Mec�nica', '3')," 
				+ "('Mec�nica', '3')," 
				+ "('Termodin�mica', '3')," 
				+ "('Eletr�t�cnica', '3')," 
				+ "('Mec�nica dos Flu�dos', '3')," 
				+ "('Mec�nica dos S�lidos', '3'),"
				+ "('Processos de Usinagem', '3')," 
				+ "('Transfer�ncia de Calor', '3'),"
				+ "('Vibra��es', '3'),"
				+ "('Metodologia Cient�fica', '3')," 
				+ "('Probabilidade e Estat�stica', '3')," 
				+ "('C�lculo N�merico', '3'),"
				+ "('Elementos de M�quinas', '3')," 
				+ "('Metrologia e Instrumenta��o', '3')," 
				+ "('M�quinas T�rmicas', '3')," 
				+ "('M�quinas de Fluxo', '3')," 
				+ "('Cinem�tica dos Mecanismos', '3')," 
				+ "('Fadiga', '3')," 
				+ "('Processos de Fundi��o', '3')," 
				+ "('Ci�ncia, Tecnologia e Sociedade', '3')," 
				+ "('Confiabilidade', '3')," 
				+ "('Criatividade e inova��o', '3')," 
				+ "('Processos de Conforma��o', '3')," 
				+ "('Processos de Soldagem', '3')," 
				+ "('Est�gio Supervisionado', '3')," 
				+ "('Trabalho de Conclus�o de Curso', '3')," 
				+ "('Engenharia Econ�mica', '3')," 
				+ "('Engenharia de Seguran�a, Legisla��o e �tica Prof.', '3');");
	}

	@SuppressWarnings("unused")
	private static void insertPessoas(Connection con) throws Exception{
			
			funcoesSQL.insertSQLComand(con, "INSERT INTO aluno VALUES "
					+ "('1', 'Luan Alves Carvalho', '123.456.789-10', '(45)98765-4321', 'luancarvalho@gmail.com'),"
					+ "('2', 'Diogo Araujo Goncalves', '524.854.548-53', '(45)94562-4257', 'diogoaraujo@gmail.com'),"
					+ "('3', 'Sofia Gomes Oliveira', '682.542.003-01', '(45)95452-3529', 'sofigomes@gmail.com')");
			
			funcoesSQL.insertSQLComand(con, "INSERT INTO aluno VALUES "
					+ "('4', 'Anna Rodrigues Goncalves', '705.459.066-01', '(11)97250-5661', 'anna_goncalves@hotmail.com '),"
					+ "('5', 'Cau� Almeida Cavalcanti', '641.435.281-00', '(61)98014-5021', 'caua_cavalti@gmail.com'),"
					+ "('6', 'Jos� da Silva Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com'),"
					+ "('7', 'Ant�nio Cunha', '601.467.499-36', '(45)98683-4064', 'antCunha@gmail.com')");
			
			funcoesSQL.insertSQLComand(con, "INSERT INTO matalunocurso VALUES"
					+ "('1', '1', '4', '2017-04-02', 'Matriculado'),('2', '3','5','2018-01-18', 'Matriculado'),('3', '1', '6', '2015-01-17', 'Matriculado'),('4', '4', '7', '2016-03-05', 'Matriculado')");
				
			funcoesSQL.insertSQLComand(con, "INSERT INTO matalunoanoletivo VALUES"
					+ "('1', '2019', '1', '2019-01-24'), ('2', '2019', '2', '2019-01-23'), ('3', '2019', '3', '2019-01-05'), ('4', '2019', '4', '2019-01-22');");
				
			funcoesSQL.insertSQLComand(con, "INSERT INTO matalunodisc VALUES"
					+ "('1', '17'), ('1', '23'), ('1', '24'), ('2', '108'), ('2', '116'), ('2','111'), ('3', '1'), ('3','2'), ('3', '17'), ('4', '61'), ('4', '59'), ('4','62')");
				
			funcoesSQL.insertSQLComand(con, "INSERT INTO professor VALUES" 
					+ "('1', 'Roberto Gil', 'robertogbrasil@gmail.com'), ('2', 'R�mulo C�sar Silva', 'romulo_silva@gmail.com'), ('3', 'Renato Bobsin', 'bobsin_machado@gmail.com'),"
					+ "('4', 'Daniel Alberto Salinas', 'alberto_salinas@gmail.com'), ('5','Eduardo Moreira', 'edu_moreira@gmail.com'), ('6','Fernando Mucio Bando', 'fernando_bando@gmail.com'),"
					+ "('7','Jorge Habib Hanna El Khouri', 'jorge_habib@gmail.com'), ('8', 'Carlos dos Santos', 'carlossantos@gmail.com'), ('9', 'Kelly Roberta Mazzutti L�beck', 'kelly_lubeck@gmail.com')");
			
			funcoesSQL.insertSQLComand(con, "INSERT INTO discprof VALUES"
					+ "('1', '17', '1', '2019-02-18'), ('2', '23', '2', '2019-02-20'), ('3', '24', '3', '2019-02-19'), ('4', '108', '4', '2019-02-18'), ('5', '116', '5', '2019-02-22'), ('6', '111', '6', '2019-02-21'),"
					+ "('7', '1', '4', '2019-02-18'), ('8', '2', '7', '2019-02-19'), ('9', '17', '1', '2019-02-18'), ('10', '61', '8', '2019-02-23'), ('11', '59', '6', '2019-02-19'), ('12', '62', '9', '2019-02-20');");
	}
}
