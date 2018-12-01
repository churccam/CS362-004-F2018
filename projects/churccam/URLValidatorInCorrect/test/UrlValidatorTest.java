import junit.framework.TestCase;
import java.util.*;
import org.junit.Assert;

public class UrlValidatorTest extends TestCase {
    private static int assertFailCount = 0;
    public UrlValidatorTest(String testName) {
        super(testName);
    }

    static public void assertFalse(String message, boolean validate){
        if(validate != false) {
            System.out.println("Test Error: " + message);
            assertFailCount++;
        }
        else {
        	System.out.println("Test Success: " + message);
        }
    }
    static public void assertTrue(String message, boolean validate){
        if(validate != true) {
            System.out.println("Test Error: " + message);
            assertFailCount++;
        }
        else {
        	System.out.println("Test Success: " + message);
        }
    }
    public void testManualTest()
    {
        assertFailCount = 0;
    	System.out.println("\nManual testing:");
        
    	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

    	//invalid url's
        assertFalse("URL should fail: ://google.com",urlVal.isValid("://google.com"));
        assertFalse("URL should fail: http://google.com/...",urlVal.isValid("http://google.com/..."));
        assertFalse("URL should fail: http://275.678.451.445:80/test1?action=view",urlVal.isValid("http://275.678.451.445:80/test1?action=view"));
        assertFalse("URL should fail: http://www.google.com:-50",urlVal.isValid("http://www.google.com:-50"));
        assertFalse("URL should fail: http://rrr.en.wikipediA.org",urlVal.isValid("http://rrr.en.wikipediA.org"));
        
        //valid url's
        assertTrue("URL should pass: http://www.google.com/?newAction=viewnextItem",urlVal.isValid("http://www.google.com/?newAction=viewnextItem"));
        assertTrue("URL should pass: http://google.com/$location",urlVal.isValid("http://google.com/$location"));
        assertTrue("URL should pass: http://google.com/location?/",urlVal.isValid("http://google.com/location?/"));
        assertTrue("URL should pass: http://www.google.com:1000",urlVal.isValid("http://www.google.com:1000"));

        if(assertFailCount > 0)
            fail("Failed Manual Tests");
        else
            System.out.println("All Manual Testing Passed");
    }


    //PARTITION 1: SCHEME TESTING
    public void testYourFirstPartition(){
        assertFailCount = 0;
    	System.out.println("\nScheme Partition Testing:");
    	
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        
        //invalid schemes
        assertFalse("Scheme should fail: h%$*ttp",urlVal.isValid("h%$*ttp://www.google.com"));
        assertFalse("Scheme should fail: 35http",urlVal.isValid("35http[://www.google.com"));
        assertFalse("Scheme should fail: 100http",urlVal.isValid("100http://www.google.com"));
        assertFalse("Scheme should fail: *http*",urlVal.isValid("*http*://www.google.com"));


        // valid schemes
        assertTrue("Scheme should pass: http ",urlVal.isValid("http://www.google.com"));
        assertTrue("Scheme should pass: http ",urlVal.isValid("http://www.cnn.com"));
        assertTrue("Scheme should pass: http ",urlVal.isValid("http://www.wiki.com"));
        assertTrue("Scheme should pass: http ",urlVal.isValid("http://www.oregonstate.edu"));



        if(assertFailCount > 0)
            fail("Failed Scheme Testing");
        else
            System.out.println("All Scheme Testing Passed");
    }

    //PARTITION 2: AUTHORITY TESTING
    public void testYourSecondPartition(){
        assertFailCount = 0;
    	System.out.println("\nAuthority testing:");
        
    	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        
    	//invalid authorities
        assertFalse("Authority should fail: http://www-poor-formatting-format",urlVal.isValid("http://www-poor-formatting-format"));
        assertFalse("Authority should fail: http://www.---.com",urlVal.isValid("http://www.---.com"));
        assertFalse("Authority should fail: http://.dotcheck",urlVal.isValid("http://.dotcheck"));
        assertFalse("Authority should fail: http://www/badslash/edu",urlVal.isValid("http://www/badslash/edu"));
        
        //valid
        assertTrue("Authority should pass: google",urlVal.isValid("http://www.google.com"));
        assertTrue("Authority should pass: go",urlVal.isValid("http://www.go.com"));
        assertTrue("Authority should pass: cnn",urlVal.isValid("http://www.cnn.com"));
        assertTrue("Authority should pass: 244.235.244.214",urlVal.isValid("http://244.235.244.214"));

        if(assertFailCount > 0)
            fail("Failed Authority Testing");
        else
            System.out.println("All Authority Tests Passed");
    }

    //PARTITION 3: PORT TESTING
    public void testYourThirdPartition() {
        assertFailCount = 0;
        System.out.println("\nPort testing:");

        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        assertFalse("Port should fail: %%%#$#$$",urlVal.isValid("http://www.google.com:%%%#$#$$"));
        assertFalse("Port should fail: badletters",urlVal.isValid("http://www.google.com:badletters"));
        assertFalse("Port should fail: -1",urlVal.isValid("http://www.google.com:-1"));
        assertFalse("Port should fail: -15",urlVal.isValid("http://www.google.com:-15"));



        assertTrue("Port should pass: 0",urlVal.isValid("http://www.google.com:0"));
        assertTrue("Port should pass: 1",urlVal.isValid("http://www.google.com:1"));
        assertTrue("Port should pass: 100",urlVal.isValid("http://www.google.com:100"));
        assertTrue("Port should pass: 1000",urlVal.isValid("http://www.google.com:1000"));

        if(assertFailCount > 0)
            fail("Failed Port Testing ");
        else
            System.out.println("All Port Tests Passed");
    }

  //PARTITION 4: PATH TESTING
    public void testYourFourthPartition() {
        System.out.println("\nPath tests:");
        assertFailCount = 0;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        assertFalse("Path should fail: /wrong//path",urlVal.isValid("http://www.google.com/wrong//path"));
        assertFalse("Path should fail: /............/",urlVal.isValid("http://www.google.com/............/"));
        assertFalse("Path should fail: http://www.google.com:",urlVal.isValid("http://www.google.com:"));
        assertFalse("Path should fail: http://www.google.coma.99",urlVal.isValid("http://www.google.coma.99"));


        assertTrue("Path should pass: /first/goodpath",urlVal.isValid("http://www.google.com/first/goodpath"));
        assertTrue("Path should pass: /good/path#",urlVal.isValid("http://www.google.com/good/path#"));
        assertTrue("Path should pass: /anothergoodpath99",urlVal.isValid("http://www.google.com/anothergoodpath99"));
        assertTrue("Path should pass: no path",urlVal.isValid("http://www.google.com"));

        if(assertFailCount > 0)
            fail("Path Testing Failed");
        else
            System.out.println("All Path Tests Passed");
    }

   
    public void testIsValid()
    {
 	   	ResultPair[] schemes = {new ResultPair("http://", true),
 	   		   					new ResultPair("ftp://", true),
 	   		   					new ResultPair("htt://", false)};
 	       
 	   	ResultPair[] authority = {new ResultPair("www.go.com", true),
 	   		   					  new ResultPair("www.go.au", true),
 	   		   					  new ResultPair("go.notvalid", false)};
 	       
 	   	ResultPair[] port = {new ResultPair(":80", true),
 	   		   				 new ResultPair(":abc", false)};
 	       
 	   	ResultPair[] path = {new ResultPair("/test/", true),
 	   		   				 new ResultPair("/////", false)};
 	       
    	System.out.println("\n Random testing:");   
 	   	for (int i=0; i<1000; i++) {
 	   		Random random = new Random();
 	   		int randomScheme = (random.nextInt(schemes.length));
 	   		int randomAuthority = (random.nextInt(authority.length));
 	   		int randomPort = (random.nextInt(port.length));
 	   		int randomPath = (random.nextInt(path.length));
 	   	    
 	   		//randomly generate a url string for array of parts
 	   		String url = schemes[randomScheme].item;
 	   		boolean expect = schemes[randomScheme].valid;
 	   		expect = expect && authority[randomAuthority].valid;
 	   		url += authority[randomAuthority].item;
 	   		expect = expect && port[randomPort].valid;
 	   		url += port[randomPort].item;
 	   		expect = expect && path[randomPath].valid;
 	   		url += path[randomPath].item;
 	   	    
 	   		//create the url validator
 	   		UrlValidator urlVal = new UrlValidator();
 	   		if (urlVal.isValid(url) == expect) System.out.println("Test Success: " + url);
 	   		else System.out.println("Test Error: " + url + "     ---Expected Outcome != Test Outcome");
 	   	}
    
    
    
}
}