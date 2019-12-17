package IBMServiceConnection;

import java.io.File;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Collections;

import com.google.gson.Gson;
import com.ibm.watson.language_translator.v3.model.IdentifyOptions;
import com.ibm.watson.visual_recognition.v3.VisualRecognition;
import com.ibm.watson.visual_recognition.v3.model.ClassifiedImages;
import com.ibm.watson.visual_recognition.v3.model.ClassifyOptions;

import AuxiliarFunctions.JObjt;
import AuxiliarFunctions.Parser;

 
public class IBMConnected {
	
	public static String callIBM(String path) throws Exception {
	
		try {
			
		   	VisualRecognition service = new VisualRecognition("2018-03-19");  
		    IdentifyOptions iamOptions = new IdentifyOptions.Builder().apiKey("LJBTYa4_djJyv8zP_RjnVKtzgb6jQgLbj3uSbSkd42fK").build();
		    service.setIamCredentials(iamOptions);

		    ClassifyOptions options = new ClassifyOptions.Builder().imagesFile(new File(path)).imagesFilename("industrialEq.png").build();
		    
		    ClassifiedImages result = service.classify(options).execute().getResult();
		    
		    Gson gson = new Gson();
		    String json = gson.toJson(result);

		    Parser parser = new Parser();
			JObjt resultado = parser.parse(json);
			ArrayList<String> classes = new ArrayList<String>();
			System.out.println();
			String descricao = new String();
			
			DecimalFormat df = new DecimalFormat("0.##");
			
			int i = 0;
			while(i < resultado.get("images").get(0).get("classifiers").get(0).get("classes").length()){
				classes.add("Tendo " + df.format(resultado.get("images").get(0).get("classifiers").get(0).get("classes").get(i).get("score").getNumber()*100) + "% de ser "+ resultado.get("images").get(0).get("classifiers").get(0).get("classes").get(i++).get("class").getString()+ ";");
			}
			
			Collections.sort(classes);
			Collections.reverse(classes);
			
			for(int j = 0; j < classes.size(); j++) {
				descricao += classes.get(j) + " ";
			}
			
			System.out.println(descricao);
			return descricao;
			
		}catch(Exception exc) { exc.printStackTrace();}
	
		return null;
	
	}
}
