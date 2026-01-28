import React, { useState, useEffect } from 'react';
import '../styles/UserForm.css';

const UserForm = ({ user, onSubmit, onCancel }) => {

/**
 * Formulário para cadastro e edição de usuários.
 * @module UserForm
 * @param {Object} props Propriedades do componente
 * @param {Object} [props.user] Dados do usuário para edição
 * @param {Function} props.onSubmit Função chamada ao enviar o formulário
 * @returns {JSX.Element} Elemento React do formulário de usuário
 */
  const [formData, setFormData] = useState({
    name: '',
    email: '',
    password: '', // Para criação ou troca
    newPassword: '', // Para edição de senha
  });

  useEffect(() => {
    if (user) {
      setFormData({
        name: user.name || '',
        email: user.email || '',
        password: '', // Não mostra a senha atual
        newPassword: '',
      });
    }
  }, [user]);

  /**
   * Atualiza o valor de um campo do formulário.
   * @param {Object} e Evento do input
   */
  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({
      ...prev,
      [name]: value
    }));
  };

  /**
   * Envia o formulário de usuário.
   * @param {Object} e Evento do formulário
   */
  const handleSubmit = (e) => {
    e.preventDefault();
    // Se estiver editando e o campo newPassword estiver preenchido, envia como password
    const dataToSend = { ...formData };
    if (user && formData.newPassword) {
      dataToSend.password = formData.newPassword;
    }
    delete dataToSend.newPassword;
    onSubmit(dataToSend);
  };

  return (
    <div className="user-form-container">
      <h2>{user ? 'Editar Usuário' : 'Criar Novo Usuário'}</h2>
      <form onSubmit={handleSubmit} className="user-form">
        <div className="form-group">
          <label htmlFor="name">Nome:</label>
          <input
            type="text"
            id="name"
            name="name"
            value={formData.name}
            onChange={handleChange}
            required
          />
        </div>

        <div className="form-group">
          <label htmlFor="email">Email:</label>
          <input
            type="email"
            id="email"
            name="email"
            value={formData.email}
            onChange={handleChange}
            required
          />
        </div>

        {!user && (
          <div className="form-group">
            <label htmlFor="password">Senha:</label>
            <input
              type="password"
              id="password"
              name="password"
              value={formData.password}
              onChange={handleChange}
              required
            />
          </div>
        )}

        {user && (
          <div className="form-group">
            <label htmlFor="newPassword">Nova Senha:</label>
            <input
              type="password"
              id="newPassword"
              name="newPassword"
              value={formData.newPassword}
              onChange={handleChange}
              placeholder="Deixe em branco para não alterar"
            />
          </div>
        )}

        <div className="form-actions">
          <button type="submit" className="btn btn-primary">
            {user ? 'Atualizar' : 'Criar'}
          </button>
          <button type="button" className="btn btn-secondary" onClick={onCancel}>
            Cancelar
          </button>
        </div>
      </form>
    </div>
  );
};

export default UserForm;
