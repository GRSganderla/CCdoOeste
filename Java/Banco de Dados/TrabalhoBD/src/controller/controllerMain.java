package controller;
import java.sql.Connection;
import java.util.ArrayList;
import java.util.Scanner;

import comandosSQL.funcoesSQL;

public class controllerMain {
	
	public static void insertCursos(Connection con) throws Exception {
		
		funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeCurso, anoLetivo) VALUES ('Ciência da computação', '2000'),('Engenharia Elétrica', '2000'),('Engenharia Mecânica', '2000'),('Matemática', '2000');");
	}
	
	public static void insertDisc(Connection con) throws Exception {
		
		funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeCurso, nomeDisc, anoLetivo) VALUES ('Ciência da computação','Cálculo Diferencial e Integral', '2018'),('Ciência da computação','Computação I', '2018'),"
				+ "('Ciência da computação','Física Geral  e Eletricidade Básica', '2018'),('Ciência da computação','Geometria Analítica e Álgebra Linear', '2018'),('Ciência da computação','Introdução à Ciência da Computação', '2018'),"
				+ "('Ciência da computação','Lógica e Matemática Discreta', '2018'),('Ciência da computação', 'Probabilidade e Estatística', '2018'),('Ciência da computação','Algoritmos e Estrutura de Dados', '2018'),"
				+ "('Ciência da computação','Cálculo Numérico', '2018'),('Ciência da computação','Computação II', '2018'),('Ciência da computação','Conceitos de Linguagens de Programação', '2018'),"
				+ "('Ciência da computação','Introdução à Arquitetura de Computadores', '2018'),('Ciência da computação','Introdução à Engenharia de Software', '2018'),('Ciência da computação','Linguagens Formais e Autômatos', '2018'),"
				+ "('Ciência da computação','Sistemas Digitais', '2018'),('Ciência da computação','Técnicas de Redação e Metodologia Científica', '2018'),('Ciência da computação','Banco de Dados', '2018'),"
				+ "('Ciência da computação','Compiladores', '2018'),('Ciência da computação','Engenharia de Software I', '2018'),('Ciência da computação','Estágio Supervisionado', '2018'),"
				+ "('Ciência da computação','Formação Empreendedora', '2018'),('Ciência da computação','Organização e Arquitetura de Computadores', '2018'),('Ciência da computação','Projeto e Análise de Algoritmos', '2018'),"
				+ "('Ciência da computação','Redes de Computadores', '2018'),('Ciência da computação','Sistemas Operacionais', '2018'),('Ciência da computação','Computação Gráfica', '2018'),"
				+ "('Ciência da computação','Engenharia de Software II', '2018'),('Ciência da computação','Inteligência Artificial', '2018'),('Ciência da computação','Optativa I', '2018'),('Ciência da computação','Optativa II', '2018'),"
				+ "('Ciência da computação','Processamento de Imagens Digitais', '2018'),('Ciência da computação','Sistemas de Informação', '2018'),('Ciência da computação','Sistemas Distribuídos', '2018'),"
				+ "('Ciência da computação','Trabalho de Conclusão de Curso', '2018')");
		funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeCurso, nomeDisc, anoLetivo) VALUES"
				+ "('Matemática', 'Fundamentos da Matemática', '2018'),"
				+ "('Matemática', 'Geometria Analítica', '2018'),"
				+ "('Matemática', 'Geometria Euclidiana', '2018'),"
				+ "('Matemática', 'Informática Aplicada à Educação Matemática', '2018'),"
				+ "('Matemática', 'Matemática Básica', '2018'),"
				+ "('Matemática', 'Tendências em Educação Matemática', '2018'),"
				+ "('Matemática', 'Cálculo I', '2018'),"
				+ "('Matemática', 'Desenho Geométrico', '2018'),"
				+ "('Matemática', 'Didática Aplicada ao Ensino da Matemática', '2018'),"
				+ "('Matemática', 'Laboratório de Ensino de Matemática', '2018'),"
				+ "('Matemática', 'Libras', '2018'),"
				+ "('Matemática', 'Psicologia Aplicada à Educação Matemática', '2018'),"
				+ "('Matemática', 'Trigonometria e Números Complexos', '2018'),"
				+ "('Matemática', 'Álgebra Linear', '2018'),"
				+ "('Matemática', 'Cálculo II', '2018'),"
				+ "('Matemática', 'Estatística', '2018'),"
				+ "('Matemática', 'Estruturas Algébricas', '2018'),"
				+ "('Matemática', 'Estágio Supervisionado I', '2018'),"
				+ "('Matemática', 'Introdução ao Trabalho Científico', '2018'),"
				+ "('Matemática', 'Optativa', '2018'),"
				+ "('Matemática', 'Políticas Educacionais', '2018'),"
				+ "('Matemática', 'Análise Real', '2018'),"	
				+ "('Matemática', 'Cálculo III', '2018'),"
				+ "('Matemática', 'Estágio Supervisionado II', '2018'),"
				+ "('Matemática', 'Física', '2018'),"
				+ "('Matemática', 'História e Filosofia da Matemática', '2018'),"
				+ "('Matemática', 'Monografia', '2018'),"
				+ "('Matemática', 'Métodos Numéricos', '2018');");
		funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeCurso, nomeDisc, anoLetivo) VALUES"
				+ "('Engenharia Elétrica', 'Computação', '2018'),"
				+ "('Engenharia Elétrica', 'Cálculo', '2018'),"
				+ "('Engenharia Elétrica', 'Desenho Técnico', '2018'),"
				+ "('Engenharia Elétrica', 'Física I', '2018'),"
				+ "('Engenharia Elétrica', 'Geometria Analítica e Álgebra Linear', '2018'),"
				+ "('Engenharia Elétrica', 'Introdução à Engenharia Elétrica', '2018'),"
				+ "('Engenharia Elétrica', 'Laboratório de Física', '2018'),"
				+ "('Engenharia Elétrica', 'Química Tecnológica e Materiais Elétricos', '2018'),"
				+ "('Engenharia Elétrica', 'Circuitos Elétricos', '2018'),"
				+ "('Engenharia Elétrica', 'Cálculo Vetorial e Variáveis Complexas', '2018'),"
				+ "('Engenharia Elétrica', 'Equações Diferenciais', '2018'),"
				+ "('Engenharia Elétrica', 'Física II', '2018'),"
				+ "('Engenharia Elétrica', 'Laboratório de Instrumentação', '2018'),"
				+ "('Engenharia Elétrica', 'Mecânica Geral', '2018'),"
				+ "('Engenharia Elétrica', 'Probabilidades e Estatística', '2018'),"
				+ "('Engenharia Elétrica', 'Análise de Sistemas Dinâmicos', '2018'),"
				+ "('Engenharia Elétrica', 'Cálculo Numérico', '2018'),"
				+ "('Engenharia Elétrica', 'Eletromagnetismo e Conversão Eletromec. de Energia', '2018'),"
				+ "('Engenharia Elétrica', 'Eletrônica Básica', '2018'),"
				+ "('Engenharia Elétrica', 'Energia, Meio Ambiente e Desenvolvimento Sust.', '2018'),"
				+ "('Engenharia Elétrica', 'Engenharia de Segurança, Legislação e Ética Prof.', '2018'),"
				+ "('Engenharia Elétrica', 'Fenômenos de Transportes', '2018'),"
				+ "('Engenharia Elétrica', 'Medidas Elétricas e Metrologia', '2018'),"
				+ "('Engenharia Elétrica', 'Sistemas Digitais e Microprocessadores', '2018'),"
				+ "('Engenharia Elétrica', 'Técnicas de Redação e Metodologia Científica', '2018'),"
				+ "('Engenharia Elétrica', 'Controle Discreto', '2018'),"
				+ "('Engenharia Elétrica', 'Eletricidade Industrial', '2018'),"
				+ "('Engenharia Elétrica', 'Eletrônica de Potência e Sistemas Industriais', '2018'),"
				+ "('Engenharia Elétrica', 'Engenharia Econômica e Gestão de Projetos', '2018'),"
				+ "('Engenharia Elétrica', 'Introdução aos Sistemas de Energia Elétrica', '2018'),"
				+ "('Engenharia Elétrica', 'Laboratório de Aplicações de Microcontraladores', '2018'),"
				+ "('Engenharia Elétrica', 'Máquinas Elétricas e Acionamento', '2018'),"
				+ "('Engenharia Elétrica', 'Sistemas de Controle', '2018'),"
				+ "('Engenharia Elétrica', 'Comunicação Analógica e Digital', '2018'),"
				+ "('Engenharia Elétrica', 'Estágio Supervisionado', '2018'),"
				+ "('Engenharia Elétrica', 'Trabalho de Conclusão de Curso', '2018');");
		funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeCurso, nomeDisc, anoLetivo)  VALUES "
				+ "('Engenharia Mecânica','Cálculo I', '2018')," 
				+ "('Engenharia Mecânica','Desenho Técnico', '2018')," 
				+ "('Engenharia Mecânica','Física I', '2018'),"
				+ "('Engenharia Mecânica','Geometria Analítica e Álgebra Linear', '2018')," 
				+ "('Engenharia Mecânica','Introdução à Engenharia Mecânica', '2018')," 
				+ "('Engenharia Mecânica','Laboratório de Física I', '2018')," 
				+ "('Engenharia Mecânica','Química', '2018')," 
				+ "('Engenharia Mecânica','Técnicas de Redação Científica', '2018')," 
				+ "('Engenharia Mecânica','Computação', '2018')," 
				+ "('Engenharia Mecânica','Cálculo II', '2018')," 
				+ "('Engenharia Mecânica','Equações Diferenciais', '2018')," 
				+ "('Engenharia Mecânica','Física II', '2018')," 
				+ "('Engenharia Mecânica','Laboratório de Física II', '2018')," 
				+ "('Engenharia Mecânica','Materiais de Construção Mecânica', '2018')," 
				+ "('Engenharia Mecânica','Mecânica', '2018')," 
				+ "('Engenharia Mecânica','Termodinâmica', '2018')," 
				+ "('Engenharia Mecânica','Eletrótécnica', '2018')," 
				+ "('Engenharia Mecânica','Mecânica dos Fluídos', '2018')," 
				+ "('Engenharia Mecânica','Mecânica dos Sólidos', '2018'),"
				+ "('Engenharia Mecânica','Processos de Usinagem', '2018')," 
				+ "('Engenharia Mecânica','Transferência de Calor', '2018'),"
				+ "('Engenharia Mecânica','Vibrações', '2018'),"
				+ "('Engenharia Mecânica','Metodologia Científica', '2018')," 
				+ "('Engenharia Mecânica','Probabilidade e Estatística', '2018')," 
				+ "('Engenharia Mecânica','Cálculo Númerico', '2018'),"
				+ "('Engenharia Mecânica','Elementos de Máquinas', '2018')," 
				+ "('Engenharia Mecânica','Metrologia e Instrumentação', '2018')," 
				+ "('Engenharia Mecânica','Máquinas Térmicas', '2018')," 
				+ "('Engenharia Mecânica','Máquinas de Fluxo', '2018')," 
				+ "('Engenharia Mecânica','Cinemática dos Mecanismos', '2018')," 
				+ "('Engenharia Mecânica','Fadiga', '2018')," 
				+ "('Engenharia Mecânica','Processos de Fundição', '2018')," 
				+ "('Engenharia Mecânica','Ciência, Tecnologia e Sociedade', '2018')," 
				+ "('Engenharia Mecânica','Confiabilidade', '2018')," 
				+ "('Engenharia Mecânica','Criatividade e inovação', '2018')," 
				+ "('Engenharia Mecânica','Processos de Conformação', '2018')," 
				+ "('Engenharia Mecânica','Processos de Soldagem', '2018')," 
				+ "('Engenharia Mecânica','Estágio Supervisionado', '2018')," 
				+ "('Engenharia Mecânica','Trabalho de Conclusão de Curso', '2018')," 
				+ "('Engenharia Mecânica','Engenharia Econômica', '2018')," 
				+ "('Engenharia Mecânica','Engenharia de Segurança, Legislação e Ética Prof.', '2018');");
	}

	public static void insertPessoas(Connection con) throws Exception{
		
		funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeAluno, cpf, fone, email, nomeCurso) VALUES "
				+ "('Luan Alves Carvalho', '123.456.789-10', '(45)98765-4321', 'luancarvalho@gmail.com', 'Não Matriculado'),"
				+ "('Diogo Araujo Goncalves', '524.854.548-53', '(45)94562-4257', 'diogoaraujo@gmail.com', 'Não Matriculado'),"
				+ "('Sofia Gomes Oliveira', '682.542.003-01', '(45)95452-3529', 'sofigomes@gmail.com', 'Não Matriculado')");
		
		funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeAluno, cpf, fone, email, nomeCurso, dataMatCurso, anoLetivo, dataMatAnoLet, nomeDisc, nomeProf, emailProf) VALUES "
				+ "('Anna Rodrigues Goncalves', '705.459.066-01', '(11)97250-5661', 'anna_goncalves@hotmail.com ', 'Ciência da Computação', '2017-04-02', '2019', '2019-01-24', 'Banco de Dados', 'Roberto Gil', 'robertogbrasil@gmail.com'),"
				+ "('Anna Rodrigues Goncalves', '705.459.066-01', '(11)97250-5661', 'anna_goncalves@hotmail.com ', 'Ciência da Computação', '2017-04-02', '2019', '2019-01-24', 'Projeto e Análise de Algoritmos', 'Rômulo César Silva', 'romulo_silva@gmail.com'),"
				+ "('Anna Rodrigues Goncalves', '705.459.066-01', '(11)97250-5661', 'anna_goncalves@hotmail.com ', 'Ciência da Computação', '2017-04-02', '2019', '2019-01-24', 'Redes de Computadores', 'Renato Bobsin', 'bobsin_machado@gmail.com'),"
				+ "('Cauã Almeida Cavalcanti', '641.435.281-00', '(61)98014-5021', 'caua_cavalti@gmail.com', 'Engenharia Mecânica', '2018-01-18', '2019', '2019-01-23', 'Cálculo II', 'Daniel Alberto Salinas', 'alberto_salinas@gmail.com'),"
				+ "('Cauã Almeida Cavalcanti', '641.435.281-00', '(61)98014-5021', 'caua_cavalti@gmail.com', 'Engenharia Mecânica', '2018-01-18', '2019', '2019-01-23', 'Mêcanica dos Fluídos', 'Eduardo Moreira', 'edu_moreira@gmail.com'),"
				+ "('Cauã Almeida Cavalcanti', '641.435.281-00', '(61)98014-5021', 'caua_cavalti@gmail.com', 'Engenharia Mecânica', '2018-01-18', '2019', '2019-01-23', 'Laboratório de Física II', 'Fernando Mucio Bando', 'fernando_bando@gmail.com'),"
				+ "('José da Silva Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com', 'Ciência da Computação', '2015-01-17', '2019', '2019-01-05' , 'Cálculo Diferencial e Integral ' ,'Daniel Alberto Salinas', 'alberto_salinas@gmail.com'),"
				+ "('José da Silva Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com', 'Ciência da Computação', '2015-01-17', '2019', '2019-01-05' , 'Computação I' ,'Jorge Habib Hanna El Khouri', 'jorge_habib@gmail.com'),"
				+ "('José da Silva Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com', 'Ciência da Computação', '2015-01-17', '2019', '2019-01-05' , 'BD' ,'Roberto Gil', 'robertogbrasil@gmail.com'),"
				+ "('Antônio Cunha', '601.467.499-36', '(45)98683-4064', 'antCunha@gmail.com', 'Matemática', '2016-03-05', '2019', '2019-01-22', 'Monografia', 'Carlos dos Santos', 'carlossantos@gmail.com'),"
				+ "('Antônio Cunha', '601.467.499-36', '(45)98683-4064', 'antCunha@gmail.com', 'Matemática', '2016-03-05', '2019', '2019-01-22', 'Física', 'Fernando Mucio Bando', 'fernando_bando@gmail.com'),"
				+ "('Antônio Cunha', '601.467.499-36', '(45)98683-4064', 'antCunha@gmail.com', 'Matemática', '2016-03-05', '2019', '2019-01-22', 'Métodos Numéricos', 'Kelly Roberta Mazzutti Lübeck', 'kelly_lubeck@gmail.com')");
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
			
			System.out.println("\n1 - Mostrar ao futuro aluno quais os cursos disponíveis");
			System.out.println("2 - Mostrar ao futuro aluno quais as disciplinas disponíveis para um determinado cursos");
			System.out.println("3 - Mostrar quais os alunos já cadastrados, porém ainda não matriculados em nenhum curso");
			System.out.println("4 - Mostrar uma matrícula do aluno realizada");
			System.out.println("5 - Listar todos os alunos que estão matriculados na disciplina de Banco de Dados.");
			System.out.println("6 - Algoritmo para impedir de matricular um aluno. Matricular o aluno “José da Silva Lima”, porém com o nome “José S. Lima”");
			System.out.println("7 - Mostrar tabela");
			System.out.println("0 - Sair");
			System.out.print("Opção: ");
			
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
				funcoesSQL.select(con, "SELECT nomeAluno, cpf, fone, email FROM matriculaaluno where nomeAluno != 'null' AND nomeCurso = 'Não Matriculado';");
				break;
			case 4:
				funcoesSQL.select(con, "SELECT * FROM matriculaaluno WHERE nomeAluno != 'NULL' AND nomeCurso != 'Não Matriculado' AND nomeCurso != 'NULL';");
				break;
			case 5:
				funcoesSQL.select(con, "SELECT * FROM matriculaaluno where nomeDisc = 'Banco de Dados' AND nomeCurso = 'Ciência da Computação' AND nomeAluno != 'NULL';");
				break;
			case 6: 
				ArrayList<String> nomeAluno = funcoesSQL.getLinha(con, "SELECT DISTINCT nomeAluno FROM matriculaaluno where nomeAluno != 'NULL';");
				for(int i = 0, n = nomeAluno.size(); i < n; i++) {//k.b
					if(nomeAluno.get(i).equals("José da Silva Lima"))
						inserirJS2 = false;
					if(nomeAluno.get(i).equals("José S. Lima"))
						inserirJS1 = false;
				}
				System.out.println("Inserindo José S. Lima");
				if(inserirJS1) { 
					funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeAluno, cpf, fone, email, nomeCurso, dataMatCurso, anoLetivo, dataMatAnoLet, nomeDisc, nomeProf, emailProf) VALUES ('José S. Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com', 'Ciência da Computação', '2015-01-17', '2019', '2019-01-05' , 'PAA' ,'Rômulo César Silva', 'romulo_silva@gmail.com')");
					System.out.println("José S. Lima INSERIDO");
				}
				else
					System.out.println("José S. Lima Não INSERIDO");
				
				System.out.println("Inserindo José da Silva Lima");
				if(inserirJS2) { 
					funcoesSQL.insertSQLComand(con, "INSERT INTO matriculaaluno (nomeAluno, cpf, fone, email, nomeCurso, dataMatCurso, anoLetivo, dataMatAnoLet, nomeDisc, nomeProf, emailProf) VALUES ('José da Silva Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com', 'Ciência da Computação', '2015-01-17', '2019', '2019-01-05' , 'PAA' ,'Rômulo César Silva', 'romulo_silva@gmail.com')");
					System.out.println("José da Silva Lima INSERIDO");
				}
				else
					System.out.println("José da Silva Lima Não INSERIDO");
				
				funcoesSQL.select(con, "SELECT * FROM matriculaaluno WHERE nomeAluno != 'NULL' AND nomeCurso != 'Não Matriculado' AND nomeCurso != 'NULL';");
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