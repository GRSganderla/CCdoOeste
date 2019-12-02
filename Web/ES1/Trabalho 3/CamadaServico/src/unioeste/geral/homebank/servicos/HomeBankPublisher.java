package unioeste.geral.homebank.servicos;

import javax.xml.ws.Endpoint;

public class HomeBankPublisher {
	
	public static void main(String[] args) {
		Endpoint.publish("http://localhost:9877/homebankWS", new HomeBankImpl());
	}	
}
