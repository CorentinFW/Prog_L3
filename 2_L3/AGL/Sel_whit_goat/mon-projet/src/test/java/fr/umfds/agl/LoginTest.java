package fr.umfds.agl;

import org.junit.jupiter.api.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.WebElement;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class LoginTest extends BaseForTests{

    @Test
    void successfulLogin()  {
        login("Chef", "mdp");
        assertTrue(driver.getTitle().contains("Page des TER de M1"));
    }

    @Test
    void passwordError(){
        login("Chef", "erreur");
        WebElement  error= driver.findElement(By.className("alert-danger"));
        String errorText=read(error);
        assertTrue(errorText.contains("Bad credentials"));
    }

}
