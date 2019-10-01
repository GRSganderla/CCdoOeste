package unioeste.geral.endereco.servicos;

import unioeste.geral.endereco.bo.Cidade;
import unioeste.geral.endereco.bo.Endereco;
import unioeste.geral.endereco.bo.EnderecoEspecifico;
import unioeste.geral.endereco.manager.UCEnderecoGeralServicos;

public class Server {

	public static Object[] endEspService(String site) throws Exception {
		
		UCEnderecoGeralServicos a = new UCEnderecoGeralServicos();
		
		EnderecoEspecifico end = a.obterEnderecoExterno(site);
		
		return new Object[] { end.getEnd().getCEP(), end.getEnd().getLougradouro().getNomeLougradouro(), end.getNroCasa(), end.getComplemento(), end.getEnd().getBairro().getNomeBairro(),
				end.getEnd().getCidade().getNomeCidade(), end.getEnd().getCidade().getUF().getNomeUF(), end.getEnd().getCidade().getUF().getPais().getNomePais()};
	}

	public static Object[] endCepService(String CEP) throws Exception{
		
		UCEnderecoGeralServicos a = new UCEnderecoGeralServicos();
		
		Endereco end = a.obterEnderecoPorCEP(CEP);
		
		return new Object[] {end.getLougradouro().getNomeLougradouro(), end.getBairro().getNomeBairro(), end.getCEP(), end.getCidade().getNomeCidade(), end.getCidade().getUF().getNomeUF(),
				end.getCidade().getUF().getPais().getNomePais()};
	}
	
	public static Object[] endIdService(int id) throws Exception{
		
		UCEnderecoGeralServicos a = new UCEnderecoGeralServicos();
		
		Endereco end = new Endereco();
		end.setIdEndereco(id);
		end = a.obterEnderecoPorID(end);
		
		return new Object[] {end.getLougradouro().getNomeLougradouro(), end.getBairro().getNomeBairro(),end.getCEP(), end.getCidade().getNomeCidade(), end.getCidade().getUF().getNomeUF(),
				end.getCidade().getUF().getPais().getNomePais()};
	}
	
	public static Object[] cidService(int id) throws Exception {
		
		UCEnderecoGeralServicos a = new UCEnderecoGeralServicos();
		
		Cidade cid = new Cidade();
		cid.setIdCidade(id);
		cid = a.obterCidade(cid);
		
		return new Object[] {cid.getNomeCidade(), cid.getUF().getNomeUF(), cid.getUF().getPais().getNomePais()};
		
	}
}
