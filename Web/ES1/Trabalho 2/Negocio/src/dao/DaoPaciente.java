package dao;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import unioeste.classesbo.CPF;
import unioeste.classesbo.Endereco;
import unioeste.classesbo.Pessoa;
import unioeste.classesbo.Sexo;
import unioeste.classesbo.especificas.Paciente;

public class DaoPaciente {
	
	public int inserePaciente(Paciente paciente, Connection con) throws SQLException {
		
		String sql = "INSERT INTO paciente (PrimeiroNome, NomeMeio, UltimoNome, CPF, Complemento, NroCasa, DtNascimento, TipoSanguineo, sexo_idSexo) VALUES (?,?,?,?,?,?,?,?,?)";
		
		PreparedStatement create = con.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS);
		create.setString(1,paciente.getPessoa().getPrimeiroNome());
		create.setString(2,paciente.getPessoa().getNomeMeio());
		create.setString(3,paciente.getPessoa().getUltimoNome());
		create.setString(4, paciente.getPessoa().getCPF().getCPF());
		create.setString(5,paciente.getPessoa().getComplemento());
		create.setInt(6,paciente.getPessoa().getNroCasa());
		create.setString(7,paciente.getPessoa().getDtNascimento());
		create.setString(8,paciente.getPessoa().getTipoSanguineo());
		create.setInt(9,paciente.getPessoa().getSexo().getIdSexo());
		//create.setInt(9,1);
		//create.setInt(10,1);
		create.setString(10,paciente.getPessoa().getEnderecoCEP().getCEP());
		create.execute();
		ResultSet generatedKeys;
		try {
			generatedKeys = create.getGeneratedKeys();
			generatedKeys.next();
		    return generatedKeys.getInt(1);
		} catch (Exception e) {
			System.out.println(e.getMessage());
		    return 0;
		}
	}
	
	public Paciente consultar(String cpf, Connection con) throws SQLException {
		String sql = "SELECT paciente.*, sexo.* FROM paciente"
				+ " INNER JOIN sexo ON sexo.idSexo = paciente.sexo_idSexo"
				+ " WHERE paciente.cpf = ?;";
		PreparedStatement stt = con.prepareStatement(sql);
		stt.setString(1, cpf);
		ResultSet res = stt.executeQuery();
		if (!res.next()) {
			return null;
		}
		Paciente paciente = new Paciente();
		Pessoa pessoa = new Pessoa();
		Sexo sexo = new Sexo();
		Endereco end = new Endereco();
		sexo.setIdSexo(res.getInt("sexo_idSexo"));
		paciente.setIdPaciente(res.getInt("idPaciente"));
		pessoa.setPrimeiroNome(res.getString("PrimeiroNome"));
		pessoa.setNomeMeio(res.getString("NomeMeio"));
		pessoa.setUltimoNome(res.getString("UltimoNome"));
		
		CPF cp = new CPF();
		cp.setCPF(res.getString("CPF"));
		
		pessoa.setCPF(cp);
		pessoa.setComplemento(res.getString("Complemento"));
		pessoa.setNroCasa(res.getInt("NroCasa"));
		pessoa.setDtNascimento(res.getString("DtNascimento"));
		pessoa.setTipoSanguineo(res.getString("TipoSanguineo"));
		pessoa.setSexo(sexo);
		pessoa.setEnderecoCEP(end);
		paciente.setPessoa(pessoa);
		return paciente;
	}
	
}
