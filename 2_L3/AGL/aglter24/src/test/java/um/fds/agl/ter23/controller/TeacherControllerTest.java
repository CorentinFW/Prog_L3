package um.fds.agl.ter23.controller;


import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit.jupiter.SpringExtension;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import um.fds.agl.ter23.services.TeacherService;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assumptions.assumingThat;
import static org.springframework.test.util.AssertionErrors.assertTrue;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.get;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.post;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;
import org.springframework.security.test.context.support.WithMockUser;

@ExtendWith(SpringExtension.class)
@SpringBootTest
@AutoConfigureMockMvc

public class TeacherControllerTest {
    @Autowired
    private MockMvc mvc;
    @Autowired
    private TeacherService teacherService;


    @Test
    @WithMockUser(username = "Chef", roles = "MANAGER")
    public void addTeacherGet() throws Exception {
        MvcResult result = mvc.perform(get("/addTeacher"))
                .andExpect(status().isOk())
                .andExpect(content().contentType("text/html;charset=UTF8"))
                .andExpect(view().name("addTeacher"))
                .andReturn();
    }

    @Test
    @WithMockUser(username = "Chef", roles = "MANAGER")
    void addTeacherPostNonExistingTeacher() throws Exception {
        assumingThat(teacherService.getTeacher(10l).isEmpty(),()-> {
            MvcResult result = mvc.perform(post("/addTeacher")
                            .param("firstName", "Anne-Marie")
                            .param("lastName", "Kermarrec")
                            .param("id", "10"))
                    .andExpect(status().is3xxRedirection())
                    .andReturn();
            assertNotNull(teacherService.findByLastName("Kermarrec"));
        });
    }



    @Test
    @WithMockUser(username = "Chef", roles = "MANAGER")
    public void addTeacherPostExistingTeacher() throws Exception {
        assumingThat(teacherService.getTeacher(10l).isEmpty(),()-> {
            MvcResult result = mvc.perform(post("/addTeacher")
                                    .param("firstName", "Anne-Marie")
                                    .param("lastName", "Kermarrec")
                                    .param("id", "10"))
                            .andExpect(status().is3xxRedirection())
                            .andReturn();
            assertEquals(teacherService.getTeacher(10l).get().getLastName(),"Kermarrec");
        });
    }

}
