<template>

    <div class="login-wrap">
        <div class="ms-login">

            <el-row>
                <el-form :model="ruleForm" :rules="rules" ref="ruleForm" label-width="10px" class="demo-ruleForm">

                    <div class="ms-title"><span>SafeChat</span></div>

                    <el-form-item prop="username">
                        <el-input v-model="ruleForm.username" placeholder="username"></el-input>
                    </el-form-item>

                    <el-form-item prop="password">
                        <el-input type="password" placeholder="password" v-model="ruleForm.password"
                            @keyup.enter.native="submitForm('ruleForm')"></el-input>
                    </el-form-item>

                    <div class="login-btn">
                        <el-button type="primary" @click="submitForm('ruleForm')">登录</el-button>
                    </div>
                </el-form>
            </el-row>

        </div>
    </div>
</template>

<script>
export default {
    name: 'myLogin',
    data: function () {
        return {
            ruleForm: {
                username: '',
                password: ''
            },
            rules: {
                username: [
                    { required: true, message: '请输入用户名', trigger: 'blur' }
                ],
                password: [
                    { required: true, message: '请输入密码', trigger: 'blur' }
                ]
            }
        }
    },
    methods: {
        submitForm(formName) {
            // this.$refs[formName].validate((valid) => {
            //     if (valid) {
            //         var user = {
            //             accnt: this.ruleForm.username,
            //             passwd: this.ruleForm.password
            //         }
            //         login(user).then(res => {
            //             switch (res.status) {
            //                 case true:
            //                     this.$router.push('/main')
            //                     break
            //             }
            //         }
            //         )
            //     }

            // })
            console.log(formName);

        }
    }
}
</script>

<style scoped>
.login-wrap {
    width: 100%;
    height: 45%;
    -webkit-border-radius: 5px;
    border-radius: 5px;
    -moz-border-radius: 5px;
    background-clip: padding-box;
    margin: 180px auto;
    width: 350px;
    padding: 35px 35px 15px 35px;
    background: #fff;
    border: 1px solid #eaeaea;
    box-shadow: 0 0 25px #cac6c6;
}

.ms-title {
    margin: -30px auto 40px auto;
    text-align: center;
    font-size: 30px;
    color: #505458;
}

.ms-login {
    position: absolute;
    left: 50%;
    top: 50%;
    width: 300px;
    height: 160px;
    margin: -150px 0 0 -190px;
    padding: 40px;
    border-radius: 5px;
    background: #fff;
}

.login-btn {
    text-align: center;
}

.login-btn button {
    width: 100%;
    height: 36px;
}
</style>