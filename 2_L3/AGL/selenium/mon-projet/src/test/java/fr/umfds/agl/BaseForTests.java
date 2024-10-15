package fr.umfds.agl;
import org.apache.commons.io.FileUtils;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.AfterEach;
import org.openqa.selenium.*;
import org.openqa.selenium.firefox.FirefoxBinary;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.openqa.selenium.firefox.FirefoxOptions;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.io.File;
import java.io.IOException;
import java.time.Duration;


public class BaseForTests {
    static WebDriver driver;
    String serverAdress="http://localhost:8080";

    protected WebDriverWait wait;

    @BeforeAll
    static void setup() {
        System.setProperty("webdriver.gecko.driver","/home/e20200009072/tmp/geckodriver-v0.35.0-linux64/geckodriver"); // A reprendre ici !
    }

    @BeforeEach
    void init() {
        FirefoxOptions options=new FirefoxOptions();//le usr sera peut etre a changer
        FirefoxBinary binary=new FirefoxBinary(new File("/usr/lib/firefox/firefox"));// ici indiquer le chemin vers firefox (which ...)
        options.setBinary(binary);
        driver=new FirefoxDriver(options);
//        driver = WebDriverManager.chromiumdriver().create();
        Duration d = Duration.ofSeconds(1);
        wait = new WebDriverWait(driver, d);

    }
    @AfterEach
    public void afterScenario(){
        driver.quit();
    }

    public void waitElement(WebElement element) {
        wait.until(ExpectedConditions.visibilityOf(element));
    }

    public void click(WebElement element) {
        waitElement(element);
        element.click();
    }

    public void write(WebElement element, String text) {
        waitElement(element);
        element.sendKeys(text);

    }

    public String read(WebElement element) {
        waitElement(element);
        return element.getText();
    }

    public  void screenshot(String fileName)
            throws IOException
    {
        File File = ((TakesScreenshot)driver)
                .getScreenshotAs(OutputType.FILE);
        String home = System.getenv("HOME");
        FileUtils.copyFile(File,
                new File(home+"/tmp/selenium/"+ this.getClass().getName()+"-"+fileName + ".jpeg"));
    }

    void login(String userName, String password)  {
        driver.get(serverAdress+"/login");
        WebElement userNameField = driver.findElement(By.id("username"));
        WebElement passwordField = driver.findElement(By.id("password"));
        WebElement loginButton = driver.findElement(By.cssSelector("[type=submit]"));

        write(userNameField, userName);
        write(passwordField, password);
        click(loginButton);
    }
}
