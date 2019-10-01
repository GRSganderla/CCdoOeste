package unioeste.geral.endereco.col;

import java.io.IOException;

import org.jsoup.Jsoup;

import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import unioeste.geral.endereco.bo.*;

public class ColEnderecoEspecifico {
	
	public String getEndereco(String site) {
		
		String txt = null;
		Document doc = null;
		
		try {
			doc = Jsoup.connect(site).get();
		} catch (IOException e) {

			e.printStackTrace();
		}
		
		Elements endereco = doc.select("p");
		
		for(Element src: endereco){

			if(src.hasClass("title__address js-address")) {
					
				txt = src.text();
			}
		}
		
		return txt;	
	}

	public String getNomePelaSigla(String sigla) {
		
		if(sigla.compareTo("RJ") == 0) return "Rio de Janeiro";
		else if(sigla.compareTo("SP") == 0) return "São Paulo";
		else if(sigla.compareTo("SC") == 0) return "Santa Catarina";
		else if(sigla.compareTo("PR") == 0) return "Paraná";
		else if(sigla.compareTo("MT") == 0) return "Mato Grosso";
		else if(sigla.compareTo("AC") == 0) return "Acre";
		else if(sigla.compareTo("AL") == 0) return "Alagoas";
		else if(sigla.compareTo("AP") == 0) return "Amapá";
		else if(sigla.compareTo("AM") == 0) return "Amazonas";
		else if(sigla.compareTo("BA") == 0) return "Bahia";
		else if(sigla.compareTo("CE") == 0) return "Ceará";
		else if(sigla.compareTo("DF") == 0) return "Distrito Federal";
		else if(sigla.compareTo("ES") == 0) return "Espírito Santo";
		else if(sigla.compareTo("GO") == 0) return "Goiás";
		else if(sigla.compareTo("MA") == 0) return "Maranhão";
		else if(sigla.compareTo("MS") == 0) return "Mato Grosso do Sul";
		else if(sigla.compareTo("MS") == 0) return "Minas Gerais";
		else if(sigla.compareTo("PA") == 0) return "Pará";
		else if(sigla.compareTo("PB") == 0) return "Paraíba";
		else if(sigla.compareTo("PE") == 0) return "Pernambuco";
		else if(sigla.compareTo("PI") == 0) return "Piauí";
		else if(sigla.compareTo("RR") == 0) return "Roraima";
		else if(sigla.compareTo("RN") == 0) return "Rio Grande do Norte";
		else if(sigla.compareTo("RS") == 0) return "Rio Grande do Sul";
		else if(sigla.compareTo("SE") == 0) return "Sergipe";
		else if(sigla.compareTo("TO") == 0) return "Tocantins";
		else if(sigla.compareTo("RO") == 0) return "Rondônia";
		
		return "Estado não Divulgado";
		
	}
	
	public EnderecoEspecifico getEnderecoEspecifico(String site) {
		
		EnderecoEspecifico esp = new EnderecoEspecifico();
		Endereco end = new Endereco();
		Lougradouro lou = new Lougradouro();
		
		String strEnd = getEndereco(site);
		String subEnd[] = strEnd.split(",");
		
		String lougradouro = subEnd[0];
		lou.setNomeLougradouro(lougradouro);
		
		String sub1[] = subEnd[1].split("-");
		String sub2[] = subEnd[2].split("-");
		
		int nro = Integer.parseInt(sub1[0].replaceAll("\\s+", ""));
		esp.setNroCasa(nro);
		
		String bairro = sub1[1].replaceFirst("\\s+", "");
		
		Bairro bai = new Bairro();
		bai.setNomeBairro(bairro);
		
		String cidade = sub2[0].replaceFirst("\\s+", "");
		
		Cidade cid = new Cidade();
		cid.setNomeCidade(cidade);
		
		String struf = sub2[1].replaceFirst("\\s+", "");
		
		UF estado = new UF();
		String nomeEstado = getNomePelaSigla(struf);
		estado.setNomeUF(nomeEstado);
		cid.setUF(estado);
		
		Pais pas = new Pais();
		pas.setNomePais("Brasil");
		
		estado.setPais(pas);
		
		end.setCEP("22441-090");
		end.setBairro(bai);
		end.setCidade(cid);
		end.setLougradouro(lou);
		
		esp.setEnd(end);
		
		return esp;
	}
	
}
