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
					if(nomeAluno.get(i).equals("José da Silva Lima"))
						inserirJS2 = false;
					if(nomeAluno.get(i).equals("José S. Lima"))
						inserirJS1 = false;
				}
				System.out.print("\nInserindo José S. Lima: ");
				if(inserirJS1) { 
					funcoesSQL.insertSQLComand(con, "INSERT INTO aluno (codAluno, nome, cpf, fone, email) VALUES ('8', 'José S. Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com');");
					System.out.print("INSERIDO");
				}
				else
					System.out.println("Não INSERIDO");
				
				System.out.print("\nInserindo José da Silva Lima: ");
				if(inserirJS2) { 
					funcoesSQL.insertSQLComand(con, "INSERT INTO aluno (codAluno, nome, cpf, fone, email) VALUES ('8', 'José da Silva Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com');");
					System.out.println("INSERIDO");
				}
				else
					System.out.println("Não INSERIDO");
				
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
		
		//funcoesSQL.insertSQLComand(con, "DELETE FROM aluno where nome = 'José S. Lima'; ");
		scan.close();
		con.close();
	}

	@SuppressWarnings("unused")
	private static void insertCursos(Connection con) throws Exception {
		
		funcoesSQL.insertSQLComand(con, "INSERT INTO curso VALUES ( '1', 'Ciência da computação', 'CC'),('2','Engenharia Elétrica', 'EE'),('3', 'Engenharia Mecânica', 'EM'),('4', 'Matemática', 'MAT');");
	}

	@SuppressWarnings("unused")
	private static void insertDisc(Connection con) throws Exception {
		
		funcoesSQL.insertSQLComand(con, "INSERT INTO disciplina (nomeDisc, idCurso) VALUES"
				+ "('Cálculo Diferencial e Integral', '1'),"
				+ "('Computação I', '1'),"
				+ "('Física Geral  e Eletricidade Básica', '1'),"
				+ "('Geometria Analítica e Álgebra Linear', '1'),"
				+ "('Introdução à Ciência da Computação','1'),"
				+ "('Lógica e Matemática Discreta','1'),"
				+ "('Probabilidade e Estatística', '1'),"
				+ "('Algoritmos e Estrutura de Dados', '1'),"
				+ "('Cálculo Numérico', '1'),"
				+ "('Computação II', '1'),"
				+ "('Conceitos de Linguagens de Programação', '1'),"
				+ "('Introdução à Arquitetura de Computadores', '1'),"
				+ "('Introdução à Engenharia de Software', '1'),"
				+ "('Linguagens Formais e Autômatos', '1'),"
				+ "('Sistemas Digitais', '1'),"
				+ "('Técnicas de Redação e Metodologia Científica', '1'),"
				+ "('Banco de Dados', '1'),"
				+ "('Compiladores', '1'),"
				+ "('Engenharia de Software I', '1'),"
				+ "('Estágio Supervisionado', '1'),"
				+ "('Formação Empreendedora', '1'),"
				+ "('Organização e Arquitetura de Computadores','1'),"
				+ "('Projeto e Análise de Algoritmos','1'),"
				+ "('Redes de Computadores','1'),"
				+ "('Sistemas Operacionais', '1'),"
				+ "('Computação Gráfica', '1'),"
				+ "('Engenharia de Software II', '1'),"
				+ "('Inteligência Artificial', '1'),"
				+ "('Optativa I', '1'),"
				+ "('Optativa II', '1'),"
				+ "('Processamento de Imagens Digitais', '1'),"
				+ "('Sistemas de Informação', '1'),"
				+ "('Sistemas Distribuídos', '1'),"
				+ "('Trabalho de Conclusão de Curso', '1');");
		funcoesSQL.insertSQLComand(con, "INSERT INTO disciplina (nomeDisc, idCurso) VALUES"
				+ "('Fundamentos da Matemática', '4'),"
				+ "('Geometria Analítica', '4'),"
				+ "('Geometria Euclidiana', '4'),"
				+ "('Informática Aplicada à Educação Matemática', '4'),"
				+ "('Matemática Básica', '4'),"
				+ "('Tendências em Educação Matemática', '4'),"
				+ "('Cálculo I', '4'),"
				+ "('Desenho Geométrico', '4'),"
				+ "('Didática Aplicada ao Ensino da Matemática', '4'),"
				+ "('Laboratório de Ensino de Matemática', '4'),"
				+ "('Libras', '4'),"
				+ "('Psicologia Aplicada à Educação Matemática', '4'),"
				+ "('Trigonometria e Números Complexos', '4'),"
				+ "('Álgebra Linear', '4'),"
				+ "('Cálculo II', '4'),"
				+ "('Estatística', '4'),"
				+ "('Estruturas Algébricas', '4'),"
				+ "('Estágio Supervisionado I', '4'),"
				+ "('Introdução ao Trabalho Científico', '4'),"
				+ "('Optativa', '4'),"
				+ "('Políticas Educacionais', '4'),"
				+ "('Análise Real', '4'),"	
				+ "('Cálculo III', '4'),"
				+ "('Estágio Supervisionado II', '4'),"
				+ "('Física', '4'),"
				+ "('História e Filosofia da Matemática', '4'),"
				+ "('Monografia', '4'),"
				+ "('Métodos Numéricos', '4');");
		funcoesSQL.insertSQLComand(con, "INSERT INTO disciplina (nomeDisc, idCurso) VALUES"
				+ "('Computação', '2'),"
				+ "('Cálculo', '2'),"
				+ "('Desenho Técnico', '2'),"
				+ "('Física I', '2'),"
				+ "('Geometria Analítica e Álgebra Linear', '2'),"
				+ "('Introdução à Engenharia Elétrica', '2'),"
				+ "('Laboratório de Física', '2'),"
				+ "('Química Tecnológica e Materiais Elétricos', '2'),"
				+ "('Circuitos Elétricos', '2'),"
				+ "('Cálculo Vetorial e Variáveis Complexas', '2'),"
				+ "('Equações Diferenciais', '2'),"
				+ "('Física II', '2'),"
				+ "('Laboratório de Instrumentação', '2'),"
				+ "('Mecânica Geral', '2'),"
				+ "('Probabilidades e Estatística', '2'),"
				+ "('Análise de Sistemas Dinâmicos', '2'),"
				+ "('Cálculo Numérico', '2'),"
				+ "('Eletromagnetismo e Conversão Eletromec. de Energia', '2'),"
				+ "('Eletrônica Básica', '2'),"
				+ "('Energia, Meio Ambiente e Desenvolvimento Sust.', '2'),"
				+ "('Engenharia de Segurança, Legislação e Ética Prof.', '2'),"
				+ "('Fenômenos de Transportes', '2'),"
				+ "('Medidas Elétricas e Metrologia', '2'),"
				+ "('Sistemas Digitais e Microprocessadores', '2'),"
				+ "('Técnicas de Redação e Metodologia Científica', '2'),"
				+ "('Controle Discreto', '2'),"
				+ "('Eletricidade Industrial', '2'),"
				+ "('Eletrônica de Potência e Sistemas Industriais', '2'),"
				+ "('Engenharia Econômica e Gestão de Projetos', '2'),"
				+ "('Introdução aos Sistemas de Energia Elétrica', '2'),"
				+ "('Laboratório de Aplicações de Microcontraladores', '2'),"
				+ "('Máquinas Elétricas e Acionamento', '2'),"
				+ "('Sistemas de Controle', '2'),"
				+ "('Comunicação Analógica e Digital', '2'),"
				+ "('Estágio Supervisionado', '2'),"
				+ "('Trabalho de Conclusão de Curso', '2');");
		funcoesSQL.insertSQLComand(con, "INSERT INTO disciplina (nomeDisc, idCurso)  VALUES"
				+ "('Cálculo I', '3')," 
				+ "('Desenho Técnico', '3')," 
				+ "('Física I', '3'),"
				+ "('Geometria Analítica e Álgebra Linear', '3')," 
				+ "('Introdução à Engenharia Mecânica', '3')," 
				+ "('Laboratório de Física I', '3')," 
				+ "('Química', '3')," 
				+ "('Técnicas de Redação Científica', '3')," 
				+ "('Computação', '3')," 
				+ "('Cálculo II', '3')," 
				+ "('Equações Diferenciais', '3')," 
				+ "('Física II', '3')," 
				+ "('Laboratório de Física II', '3')," 
				+ "('Materiais de Construção Mecânica', '3')," 
				+ "('Mecânica', '3')," 
				+ "('Termodinâmica', '3')," 
				+ "('Eletrótécnica', '3')," 
				+ "('Mecânica dos Fluídos', '3')," 
				+ "('Mecânica dos Sólidos', '3'),"
				+ "('Processos de Usinagem', '3')," 
				+ "('Transferência de Calor', '3'),"
				+ "('Vibrações', '3'),"
				+ "('Metodologia Científica', '3')," 
				+ "('Probabilidade e Estatística', '3')," 
				+ "('Cálculo Númerico', '3'),"
				+ "('Elementos de Máquinas', '3')," 
				+ "('Metrologia e Instrumentação', '3')," 
				+ "('Máquinas Térmicas', '3')," 
				+ "('Máquinas de Fluxo', '3')," 
				+ "('Cinemática dos Mecanismos', '3')," 
				+ "('Fadiga', '3')," 
				+ "('Processos de Fundição', '3')," 
				+ "('Ciência, Tecnologia e Sociedade', '3')," 
				+ "('Confiabilidade', '3')," 
				+ "('Criatividade e inovação', '3')," 
				+ "('Processos de Conformação', '3')," 
				+ "('Processos de Soldagem', '3')," 
				+ "('Estágio Supervisionado', '3')," 
				+ "('Trabalho de Conclusão de Curso', '3')," 
				+ "('Engenharia Econômica', '3')," 
				+ "('Engenharia de Segurança, Legislação e Ética Prof.', '3');");
	}

	@SuppressWarnings("unused")
	private static void insertPessoas(Connection con) throws Exception{
			
			funcoesSQL.insertSQLComand(con, "INSERT INTO aluno VALUES "
					+ "('1', 'Luan Alves Carvalho', '123.456.789-10', '(45)98765-4321', 'luancarvalho@gmail.com'),"
					+ "('2', 'Diogo Araujo Goncalves', '524.854.548-53', '(45)94562-4257', 'diogoaraujo@gmail.com'),"
					+ "('3', 'Sofia Gomes Oliveira', '682.542.003-01', '(45)95452-3529', 'sofigomes@gmail.com')");
			
			funcoesSQL.insertSQLComand(con, "INSERT INTO aluno VALUES "
					+ "('4', 'Anna Rodrigues Goncalves', '705.459.066-01', '(11)97250-5661', 'anna_goncalves@hotmail.com '),"
					+ "('5', 'Cauã Almeida Cavalcanti', '641.435.281-00', '(61)98014-5021', 'caua_cavalti@gmail.com'),"
					+ "('6', 'José da Silva Lima', '293.566.147-84' , '(41)95718-2387', 'jose_lima@live.com'),"
					+ "('7', 'Antônio Cunha', '601.467.499-36', '(45)98683-4064', 'antCunha@gmail.com')");
			
			funcoesSQL.insertSQLComand(con, "INSERT INTO matalunocurso VALUES"
					+ "('1', '1', '4', '2017-04-02', 'Matriculado'),('2', '3','5','2018-01-18', 'Matriculado'),('3', '1', '6', '2015-01-17', 'Matriculado'),('4', '4', '7', '2016-03-05', 'Matriculado')");
				
			funcoesSQL.insertSQLComand(con, "INSERT INTO matalunoanoletivo VALUES"
					+ "('1', '2019', '1', '2019-01-24'), ('2', '2019', '2', '2019-01-23'), ('3', '2019', '3', '2019-01-05'), ('4', '2019', '4', '2019-01-22');");
				
			funcoesSQL.insertSQLComand(con, "INSERT INTO matalunodisc VALUES"
					+ "('1', '17'), ('1', '23'), ('1', '24'), ('2', '108'), ('2', '116'), ('2','111'), ('3', '1'), ('3','2'), ('3', '17'), ('4', '61'), ('4', '59'), ('4','62')");
				
			funcoesSQL.insertSQLComand(con, "INSERT INTO professor VALUES" 
					+ "('1', 'Roberto Gil', 'robertogbrasil@gmail.com'), ('2', 'Rômulo César Silva', 'romulo_silva@gmail.com'), ('3', 'Renato Bobsin', 'bobsin_machado@gmail.com'),"
					+ "('4', 'Daniel Alberto Salinas', 'alberto_salinas@gmail.com'), ('5','Eduardo Moreira', 'edu_moreira@gmail.com'), ('6','Fernando Mucio Bando', 'fernando_bando@gmail.com'),"
					+ "('7','Jorge Habib Hanna El Khouri', 'jorge_habib@gmail.com'), ('8', 'Carlos dos Santos', 'carlossantos@gmail.com'), ('9', 'Kelly Roberta Mazzutti Lübeck', 'kelly_lubeck@gmail.com')");
			
			funcoesSQL.insertSQLComand(con, "INSERT INTO discprof VALUES"
					+ "('1', '17', '1', '2019-02-18'), ('2', '23', '2', '2019-02-20'), ('3', '24', '3', '2019-02-19'), ('4', '108', '4', '2019-02-18'), ('5', '116', '5', '2019-02-22'), ('6', '111', '6', '2019-02-21'),"
					+ "('7', '1', '4', '2019-02-18'), ('8', '2', '7', '2019-02-19'), ('9', '17', '1', '2019-02-18'), ('10', '61', '8', '2019-02-23'), ('11', '59', '6', '2019-02-19'), ('12', '62', '9', '2019-02-20');");
	}
}
