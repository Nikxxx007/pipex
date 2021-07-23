#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include <stdlib.h>

char	*ft_substr_from_to(char *str, size_t begin, size_t end);//[begin, end)
size_t	ft_strlen(const char *str);
int		ft_isspace(char c);

int		ft_strncmp(const char *str1, const char *str2, size_t len);
int		ft_strcmp(const char *str1, const char *str2);
char	*ft_strchr(char *str, int sep);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_realloc(void *str1, size_t before, size_t after);

char	**ft_split(char const *s, char c);
char	**ft_smart_split(const char *s, int (*cmp)(char), const char *tail);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		ft_islower(char c);
int		ft_isupper(char c);
int		ft_isalpha(char c);
int		ft_isdigit(char c);

#endif