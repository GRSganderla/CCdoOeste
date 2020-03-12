package controller;
import java.sql.Connection;
import java.util.ArrayList;
import java.util.Scanner;

import comandosSQL.funcoesSQL;

public class controllerMain {
	
	public static void insertCursos(Connection con) throws Exception {
		
		funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeCurso, anoLetivo) VALUES ('Ci�ncia da computa��o', '2000'),('Engenharia El�trica', '2000'),('Engenharia Mec�nica', '2000'),('Matem�tica', '2000');");
	}
	
	public static void insertDisc(Connection con) throws Exception {
		
		funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeCurso, nomeDisc, anoLetivo) VALUES ('Ci�ncia da computa��o','C�lculo Diferencial e Integral', '2018'),('Ci�ncia da computa��o','Computa��o I', '2018'),"
				+ "('Ci�ncia da computa��o','F�sica Geral  e Eletricidade B�sica', '2018'),('Ci�ncia da computa��o','Geometria Anal�tica e �lgebra Linear', '2018'),('Ci�ncia da computa��o','Introdu��o � Ci�ncia da Computa��o', '2018'),"
				+ "('Ci�ncia da computa��o','L�gica e Matem�tica Discreta', '2018'),('Ci�ncia da computa��o', 'Probabilidade e Estat�stica', '2018'),('Ci�ncia da computa��o','Algoritmos e Estrutura de Dados', '2018'),"
				+ "('Ci�ncia da computa��o','C�lculo Num�rico', '2018'),('Ci�ncia da computa��o','Computa��o II', '2018'),('Ci�ncia da computa��o','Conceitos de Linguagens de Programa��o', '2018'),"
				+ "('Ci�ncia da computa��o','Introdu��o � Arquitetura de Computadores', '2018'),('Ci�ncia da computa��o','Introdu��o � Engenharia de Software', '2018'),('Ci�ncia da computa��o','Linguagens Formais e Aut�matos', '2018'),"
				+ "('Ci�ncia da computa��o','Sistemas Digitais', '2018'),('Ci�ncia da computa��o','T�cnicas de Reda��o e Metodologia Cient�fica', '2018'),('Ci�ncia da computa��o','Banco de Dados', '2018'),"
				+ "('Ci�ncia da computa��o','Compiladores', '2018'),('Ci�ncia da computa��o','Engenharia de Software I', '2018'),('Ci�ncia da computa��o','Est�gio Supervisionado', '2018'),"
				+ "('Ci�ncia da computa��o','Forma��o Empreendedora', '2018'),('Ci�ncia da computa��o','Organiza��o e Arquitetura de Computadores', '2018'),('Ci�ncia da computa��o','Projeto e An�lise de Algoritmos', '2018'),"
				+ "('Ci�ncia da computa��o','Redes de Computadores', '2018'),('Ci�ncia da computa��o','Sistemas Operacionais', '2018'),('Ci�ncia da computa��o','Computa��o Gr�fica', '2018'),"
				+ "('Ci�ncia da computa��o','Engenharia de Software II', '2018'),('Ci�ncia da computa��o','Intelig�ncia Artificial', '2018'),('Ci�ncia da computa��o','Optativa I', '2018'),('Ci�ncia da computa��o','Optativa II', '2018'),"
				+ "('Ci�ncia da computa��o','Processamento de Imagens Digitais', '2018'),('Ci�ncia da computa��o','Sistemas de Informa��o', '2018'),('Ci�ncia da computa��o','Sistemas Distribu�dos', '2018'),"
				+ "('Ci�ncia da computa��o','Trabalho de Conclus�o de Curso', '2018')");
		funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeCurso, nomeDisc, anoLetivo) VALUES"
				+ "('Matem�tica', 'Fundamentos da Matem�tica', '2018'),"
				+ "('Matem�tica', 'Geometria Anal�tica', '2018'),"
				+ "('Matem�tica', 'Geometria Euclidiana', '2018'),"
				+ "('Matem�tica', 'Inform�tica Aplicada � Educa��o Matem�tica', '2018'),"
				+ "('Matem�tica', 'Matem�tica B�sica', '2018'),"
				+ "('Matem�tica', 'Tend�ncias em Educa��o Matem�tica', '2018'),"
				+ "('Matem�tica', 'C�lculo I', '2018'),"
				+ "('Matem�tica', 'Desenho Geom�trico', '2018'),"
				+ "('Matem�tica', 'Did�tica Aplicada ao Ensino da Matem�tica', '2018'),"
				+ "('Matem�tica', 'Laborat�rio de Ensino de Matem�tica', '2018'),"
				+ "('Matem�tica', 'Libras', '2018'),"
				+ "('Matem�tica', 'Psicologia Aplicada � Educa��o Matem�tica', '2018'),"
				+ "('Matem�tica', 'Trigonometria e N�meros Complexos', '2018'),"
				+ "('Matem�tica', '�lgebra Linear', '2018'),"
				+ "('Matem�tica', 'C�lculo II', '2018'),"
				+ "('Matem�tica', 'Estat�stica', '2018'),"
				+ "('Matem�tica', 'Estruturas Alg�bricas', '2018'),"
				+ "('Matem�tica', 'Est�gio Supervisionado I', '2018'),"
				+ "('Matem�tica', 'Introdu��o ao Trabalho Cient�fico', '2018'),"
				+ "('Matem�tica', 'Optativa', '2018'),"
				+ "('Matem�tica', 'Pol�ticas Educacionais', '2018'),"
				+ "('Matem�tica', 'An�lise Real', '2018'),"	
				+ "('Matem�tica', 'C�lculo III', '2018'),"
				+ "('Matem�tica', 'Est�gio Supervisionado II', '2018'),"
				+ "('Matem�tica', 'F�sica', '2018'),"
				+ "('Matem�tica', 'Hist�ria e Filosofia da Matem�tica', '2018'),"
				+ "('Matem�tica', 'Monografia', '2018'),"
				+ "('Matem�tica', 'M�todos Num�ricos', '2018');");
		funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeCurso, nomeDisc, anoLetivo) VALUES"
				+ "('Engenharia El�trica', 'Computa��o', '2018'),"
				+ "('Engenharia El�trica', 'C�lculo', '2018'),"
				+ "('Engenharia El�trica', 'Desenho T�cnico', '2018'),"
				+ "('Engenharia El�trica', 'F�sica I', '2018'),"
				+ "('Engenharia El�trica', 'Geometria Anal�tica e �lgebra Linear', '2018'),"
				+ "('Engenharia El�trica', 'Introdu��o � Engenharia El�trica', '2018'),"
				+ "('Engenharia El�trica', 'Laborat�rio de F�sica', '2018'),"
				+ "('Engenharia El�trica', 'Qu�mica Tecnol�gica e Materiais El�tricos', '2018'),"
				+ "('Engenharia El�trica', 'Circuitos El�tricos', '2018'),"
				+ "('Engenharia El�trica', 'C�lculo Vetorial e Vari�veis Complexas', '2018'),"
				+ "('Engenharia El�trica', 'Equa��es Diferenciais', '2018'),"
				+ "('Engenharia El�trica', 'F�sica II', '2018'),"
				+ "('Engenharia El�trica', 'Laborat�rio de Instrumenta��o', '2018'),"
				+ "('Engenharia El�trica', 'Mec�nica Geral', '2018'),"
				+ "('Engenharia El�trica', 'Probabilidades e Estat�stica', '2018'),"
				+ "('Engenharia El�trica', 'An�lise de Sistemas Din�micos', '2018'),"
				+ "('Engenharia El�trica', 'C�lculo Num�rico', '2018'),"
				+ "('Engenharia El�trica', 'Eletromagnetismo e Convers�o Eletromec. de Energia', '2018'),"
				+ "('Engenharia El�trica', 'Eletr�nica B�sica', '2018'),"
				+ "('Engenharia El�trica', 'Energia, Meio Ambiente e Desenvolvimento Sust.', '2018'),"
				+ "('Engenharia El�trica', 'Engenharia de Seguran�a, Legisla��o e �tica Prof.', '2018'),"
				+ "('Engenharia El�trica', 'Fen�menos de Transportes', '2018'),"
				+ "('Engenharia El�trica', 'Medidas El�tricas e Metrologia', '2018'),"
				+ "('Engenharia El�trica', 'Sistemas Digitais e Microprocessadores', '2018'),"
				+ "('Engenharia El�trica', 'T�cnicas de Reda��o e Metodologia Cient�fica', '2018'),"
				+ "('Engenharia El�trica', 'Controle Discreto', '2018'),"
				+ "('Engenharia El�trica', 'Eletricidade Industrial', '2018'),"
				+ "('Engenharia El�trica', 'Eletr�nica de Pot�ncia e Sistemas Industriais', '2018'),"
				+ "('Engenharia El�trica', 'Engenharia Econ�mica e Gest�o de Projetos', '2018'),"
				+ "('Engenharia El�trica', 'Introdu��o aos Sistemas de Energia El�trica', '2018'),"
				+ "('Engenharia El�trica', 'Laborat�rio de Aplica��es de Microcontraladores', '2018'),"
				+ "('Engenharia El�trica', 'M�quinas El�tricas e Acionamento', '2018'),"
				+ "('Engenharia El�trica', 'Sistemas de Controle', '2018'),"
				+ "('Engenharia El�trica', 'Comunica��o Anal�gica e Digital', '2018'),"
				+ "('Engenharia El�trica', 'Est�gio Supervisionado', '2018'),"
				+ "('Engenharia El�trica', 'Trabalho de Conclus�o de Curso', '2018');");
		funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeCurso, nomeDisc, anoLetivo)  VALUES "
				+ "('Engenharia Mec�nica','C�lculo I', '2018')," 
				+ "('Engenharia Mec�nica','Desenho T�cnico', '2018')," 
				+ "('Engenharia Mec�nica','F�sica I', '2018'),"
				+ "('Engenharia Mec�nica','Geometria Anal�tica e �lgebra Linear', '2018')," 
				+ "('Engenharia Mec�nica','Introdu��o � Engenharia Mec�nica', '2018')," 
				+ "('Engenharia Mec�nica','Laborat�rio de F�sica I', '2018')," 
				+ "('Engenharia Mec�nica','Qu�mica', '2018')," 
				+ "('Engenharia Mec�nica','T�cnicas de Reda��o Cient�fica', '2018')," 
				+ "('Engenharia Mec�nica','Computa��o', '2018')," 
				+ "('Engenharia Mec�nica','C�lculo II', '2018')," 
				+ "('Engenharia Mec�nica','Equa��es Diferenciais', '2018')," 
				+ "('Engenharia Mec�nica','F�sica II', '2018')," 
				+ "('Engenharia Mec�nica','Laborat�rio de F�sica II', '2018')," 
				+ "('Engenharia Mec�nica','Materiais de Constru��o Mec�nica', '2018')," 
				+ "('Engenharia Mec�nica','Mec�nica', '2018')," 
				+ "('Engenharia Mec�nica','Termodin�mica', '2018')," 
				+ "('Engenharia Mec�nica','Eletr�t�cnica', '2018')," 
				+ "('Engenharia Mec�nica','Mec�nica dos Flu�dos', '2018')," 
				+ "('Engenharia Mec�nica','Mec�nica dos S�lidos', '2018'),"
				+ "('Engenharia Mec�nica','Processos de Usinagem', '2018')," 
				+ "('Engenharia Mec�nica','Transfer�ncia de Calor', '2018'),"
				+ "('Engenharia Mec�nica','Vibra��es', '2018'),"
				+ "('Engenharia Mec�nica','Metodologia Cient�fica', '2018')," 
				+ "('Engenharia Mec�nica','Probabilidade e Estat�stica', '2018')," 
				+ "('Engenharia Mec�nica','C�lculo N�merico', '2018'),"
				+ "('Engenharia Mec�nica','Elementos de M�quinas', '2018')," 
				+ "('Engenharia Mec�nica','Metrologia e Instrumenta��o', '2018')," 
				+ "('Engenharia Mec�nica','M�quinas T�rmicas', '2018')," 
				+ "('Engenharia Mec�nica','M�quinas de Fluxo', '2018')," 
				+ "('Engenharia Mec�nica','Cinem�tica dos Mecanismos', '2018')," 
				+ "('Engenharia Mec�nica','Fadiga', '2018')," 
				+ "('Engenharia Mec�nica','Processos de Fundi��o', '2018')," 
				+ "('Engenharia Mec�nica','Ci�ncia, Tecnologia e Sociedade', '2018')," 
				+ "('Engenharia Mec�nica','Confiabilidade', '2018')," 
				+ "('Engenharia Mec�nica','Criatividade e inova��o', '2018')," 
				+ "('Engenharia Mec�nica','Processos de Conforma��o', '2018')," 
				+ "('Engenharia Mec�nica','Processos de Soldagem', '2018')," 
				+ "('Engenharia Mec�nica','Est�gio Supervisionado', '2018')," 
				+ "('Engenharia Mec�nica','Trabalho de Conclus�o de Curso', '2018')," 
				+ "('Engenharia Mec�nica','Engenharia Econ�mica', '2018')," 
				+ "('Engenharia Mec�nica','Engenharia de Seguran�a, Legisla��o e �tica Prof.', '2018');");
	}

	public static void insertPessoas(Connection con) throws Exception{
		
		funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeAluno, cpf, fone, email, nomeCurso) VALUES "
				+ "('Luan Alves Carvalho', '123.456.789-10', '(45)98765-4321', 'luancarvalho@gmail.com', 'N�o Matriculado'),"
				+ "('Diogo Araujo Goncalves', '524.854.548-53', '(45)94562-4257', 'diogoaraujo@gmail.com', 'N�o Matriculado'),"
				+ "('Sofia Gomes Oliveira', '682.542.003-01', '(45)95452-3529', 'sofigomes@gmail.com', 'N�o Matriculado')");
		
		funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeAluno, cpf, fone, email, nomeCurso, dataMatCurso, anoLetivo, dataMatAnoLet, nomeDisc, nomeProf, emailProf) VALUES "
				+ "('Anna Rodrigues Goncalves', '705.459.066-01', '(11)97250-5661', 'anna_goncalves@hotmail.com ', 'Ci�ncia da Computa��o', '2017-04-02', '2019', '2019-01-24', 'Banco de Dados', 'Roberto Gil', 'robertogbrasil@gmail.com'),"
				+ "('Anna Rodrigues Goncalves', '705.459.066-01', '(11)97250-5661', 'anna_goncalves@hotmail.com ', 'Ci�ncia da Computa��o', '2017-04-02', '2019', '2019-01-24', 'Projeto e An�lise de Algoritmos', 'R�mulo C�sar Silva', 'romulo_silva@gmail.com'),"
				+ "('Anna Rodrigues Goncalves', '705.459.066-01', '(11)97250-5661', 'anna_goncalves@hotmail.com ', 'Ci�ncia da Computa��o', '2017-04-02', '2019', '2019-01-24', 'Redes de Computadores', 'Renato Bobsin', 'bobsin_machado@gmail.com'),"
				+ "('Cau� Almeida Cavalcanti', '641.435.281-00', '(61)98014-5021', 'caua_cavalti@gmail.com', 'Engenharia Mec�nica', '2018-01-18', '2019', '2019-01-23', 'C�lculo II', 'Daniel Alberto Salinas', 'alberto_salinas@gmail.com'),"
				+ "('Cau� Almeida Cavalcanti', '641.435.281-00', '(61)98014-5021', 'caua_cavalti@gmail.com', 'Engenharia Mec�nica', '2018-01-18', '2019', '2019-01-23', 'M�canica dos Flu�dos', 'Eduardo Moreira', 'edu_moreira@gmail.com'),"
				+ "('Cau� Almeida Cavalcanti', '641.435.281-00', '(61)98014-5021', 'caua_cavalti@gmail.com', 'Engenharia Mec�nica', '2018-01-18', '2019', '2019-01-23', 'Laborat�rio de F�sica II', 'Fernando Mucio Bando', 'fernando_bando@gmail.com'),"
				+ "('Jos� da Silva Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com', 'Ci�ncia da Computa��o', '2015-01-17', '2019', '2019-01-05' , 'C�lculo Diferencial e Integral ' ,'Daniel Alberto Salinas', 'alberto_salinas@gmail.com'),"
				+ "('Jos� da Silva Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com', 'Ci�ncia da Computa��o', '2015-01-17', '2019', '2019-01-05' , 'Computa��o I' ,'Jorge Habib Hanna El Khouri', 'jorge_habib@gmail.com'),"
				+ "('Jos� da Silva Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com', 'Ci�ncia da Computa��o', '2015-01-17', '2019', '2019-01-05' , 'BD' ,'Roberto Gil', 'robertogbrasil@gmail.com'),"
				+ "('Ant�nio Cunha', '601.467.499-36', '(45)98683-4064', 'antCunha@gmail.com', 'Matem�tica', '2016-03-05', '2019', '2019-01-22', 'Monografia', 'Carlos dos Santos', 'carlossantos@gmail.com'),"
				+ "('Ant�nio Cunha', '601.467.499-36', '(45)98683-4064', 'antCunha@gmail.com', 'Matem�tica', '2016-03-05', '2019', '2019-01-22', 'F�sica', 'Fernando Mucio Bando', 'fernando_bando@gmail.com'),"
				+ "('Ant�nio Cunha', '601.467.499-36', '(45)98683-4064', 'antCunha@gmail.com', 'Matem�tica', '2016-03-05', '2019', '2019-01-22', 'M�todos Num�ricos', 'Kelly Roberta Mazzutti L�beck', 'kelly_lubeck@gmail.com')");
	}
	
	public static void main(String[] args) throws Exception{
		
		/*Scanner scan = new Scanner(System.in);
		int opcao = 1;
		boolean inserirJS1 = true, inserirJS2 = true;*/
		Connection con = funcoesSQL.getConnection("jdbc:mysql://localhost:3308/mydb?autoReconnect=true&useSSL=false");
		int idCliente = funcoesSQL.getLogin(con, "grodriguessganderla@hotmail.com", "1234");
		ArrayList<String> cliente = funcoesSQL.getCliente(con, idCliente);
		System.out.println(idCliente);
		System.out.println(cliente);
		/*String nomeCurso;
		controllerMain.insertCursos(con);
		controllerMain.insertDisc(con);// e , f, s.
		controllerMain.insertPessoas(con);
		
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
				funcoesSQL.select(con, "SELECT nomeCurso FROM matriculaaluno where nomeCurso != 'NULL' AND anoLetivo = '2000' order by nomeCurso;");
				break;
			case 2:
				System.out.print("Entre com o determinado curso: ");
				nomeCurso = scan.nextLine();
				System.out.println(nomeCurso);
				funcoesSQL.select(con, "SELECT nomeDisc FROM matriculaaluno where nomeCurso = '"+nomeCurso+"' AND anoLetivo = '2018' order by nomeDisc;");
				break;
			case 3:
				funcoesSQL.select(con, "SELECT nomeAluno, cpf, fone, email FROM matriculaaluno where nomeAluno != 'null' AND nomeCurso = 'N�o Matriculado';");
				break;
			case 4:
				funcoesSQL.select(con, "SELECT * FROM matriculaaluno WHERE nomeAluno != 'NULL' AND nomeCurso != 'N�o Matriculado' AND nomeCurso != 'NULL';");
				break;
			case 5:
				funcoesSQL.select(con, "SELECT * FROM matriculaaluno where nomeDisc = 'Banco de Dados' AND nomeCurso = 'Ci�ncia da Computa��o' AND nomeAluno != 'NULL';");
				break;
			case 6: 
				ArrayList<String> nomeAluno = funcoesSQL.getLinha(con, "SELECT DISTINCT nomeAluno FROM matriculaaluno where nomeAluno != 'NULL';");
				for(int i = 0, n = nomeAluno.size(); i < n; i++) {//k.b
					if(nomeAluno.get(i).equals("Jos� da Silva Lima"))
						inserirJS2 = false;
					if(nomeAluno.get(i).equals("Jos� S. Lima"))
						inserirJS1 = false;
				}
				System.out.println("Inserindo Jos� S. Lima");
				if(inserirJS1) { 
					funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeAluno, cpf, fone, email, nomeCurso, dataMatCurso, anoLetivo, dataMatAnoLet, nomeDisc, nomeProf, emailProf) VALUES ('Jos� S. Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com', 'Ci�ncia da Computa��o', '2015-01-17', '2019', '2019-01-05' , 'PAA' ,'R�mulo C�sar Silva', 'romulo_silva@gmail.com')");
					System.out.println("Jos� S. Lima INSERIDO");
				}
				else
					System.out.println("Jos� S. Lima N�o INSERIDO");
				
				System.out.println("Inserindo Jos� da Silva Lima");
				if(inserirJS2) { 
					funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeAluno, cpf, fone, email, nomeCurso, dataMatCurso, anoLetivo, dataMatAnoLet, nomeDisc, nomeProf, emailProf) VALUES ('Jos� da Silva Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com', 'Ci�ncia da Computa��o', '2015-01-17', '2019', '2019-01-05' , 'PAA' ,'R�mulo C�sar Silva', 'romulo_silva@gmail.com')");
					System.out.println("Jos� da Silva Lima INSERIDO");
				}
				else
					System.out.println("Jos� da Silva Lima N�o INSERIDO");
				
				funcoesSQL.select(con, "SELECT * FROM matriculaaluno WHERE nomeAluno != 'NULL' AND nomeCurso != 'N�o Matriculado' AND nomeCurso != 'NULL';");
				break;
			case 7:
				funcoesSQL.select(con, "SELECT * FROM matriculaaluno;");
				break;
			default:
			case 0:
				break;
			}

		}
		funcoesSQL.insertSQLComand(con, "DELETE FROM matriculaaluno");
		con.close();
		scan.close();*/
	}
}